//usman zahid
//uzahid
//asg5
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
#include <fstream>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream log (cout);
struct cix_exit: public exception {};

unordered_map<string,cix_command> command_map {
   {"exit", CIX_EXIT},
   {"help", CIX_HELP},
   {"ls"  , CIX_LS  },
   {"get", CIX_GET},
   {"rm", CIX_RM}, 
   {"put", CIX_PUT },
};

void cix_help() {
   static vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

void cix_ls (client_socket& server) {
   cix_header header;
   header.command = CIX_LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.command != CIX_LSOUT) {
      log << "sent CIX_LS, server did not return CIX_LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      cout << buffer;
   }
}


void cix_rm (client_socket& server, string filename){
    cix_header header;
    memset(header.filename, 0, FILENAME_SIZE);
    header.command = CIX_RM;
    strncpy(header.filename, filename.c_str(), FILENAME_SIZE);
    send_packet (server, &header, sizeof header);
    recv_packet (server, &header, sizeof header);
    log << "received header " << header << endl;
    if(header.command != CIX_ACK){
        log << "sent CIX_RM, server did not return CIX_ACK" << endl;
        log << "server returned " << header << endl;
    }
    else{
        log << "sent CIX_RM, return CIX_ACK, command success!" << endl;
    }
}

void cix_put (client_socket& server, string filename){
    if (filename.find_first_of("/") != string::npos){
       cout<< "invalid filename\n";
       return;
    } 
    if (filename.size() > 58) {
       cout << "The file name is invalid\n";
       return;
   } 
    cix_header header;
    header.command = CIX_PUT;
    strncpy(header.filename, filename.c_str(), FILENAME_SIZE);
    ifstream in (filename);
    if(in.fail()){
        cout << "Usage(): End Terminated" << endl;
        return;
    }
    else{
        in.seekg(0, std::ios::end);
        streamsize size = in.tellg();
        in.seekg(0, std::ios::beg);
        char buffer[size];
        in.read(buffer, size);
        header.nbytes = size;
        log << "sending header " << header << endl;
        send_packet (server, &header, sizeof header);
        send_packet (server, buffer, size);
        recv_packet (server, &header, sizeof header);
        if(header.command != CIX_ACK) {
            log << "CIX_PUT failure, server did not return CIX_ACK.."
             << endl;
            log << "server returned " << header << endl;
        }
        else{
            log << "sent CIX_PUT, return CIX_ACK, command success"
                << endl;
        }
    }
}


void cix_get (client_socket& server, string filename){
   if (filename.size() > 58) {
      cout << "The file is invalid\n";
      return;
   }
   if (filename.find_first_of("/") != string::npos) {
      cout << "invalid filename\n";
      return;
   }
    cix_header header;
    header.command = CIX_GET;
    strncpy(header.filename, filename.c_str(), FILENAME_SIZE);
    log << "Sending the header " << header << endl;
    send_packet (server, &header, sizeof header);
    recv_packet (server, &header, sizeof header);
    log << "Received header..." << header << endl;
    if(header.command != CIX_FILE) {
        log << "CIX_GET failure, server did not return CIX_FILE..."
            << endl;
        log << "Server returned:" << header << endl;
    }
    else{
        char buffer[header.nbytes];
        recv_packet (server, buffer, header.nbytes);
        log << "Received:" << header.filename << " " <<
        header.nbytes << "bytes" << endl;
        ofstream out;
        out.open(header.filename);
        out.write(buffer, header.nbytes);
        out.close();
    }
}

bool SIGINT_throw_cix_exit {false};

void signal_handler (int signal) {
    log << "Signal handler: caught " << strsignal (signal) << endl;
    switch (signal) {
        case SIGINT: case SIGTERM: SIGINT_throw_cix_exit = true; break;
        default: break;
    }
}


void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   if (args.size() == 1){
      string t = args[0]; 
      size_t accept = t.find("."); 
      if (accept == string::npos){ 
         host = get_cix_server_host (args,1); 
         port = get_cix_server_port (args,0); 
      } 
      else{ 
         host = get_cix_server_host (args, 0); 
         port = get_cix_server_port (args,1);
      }
   }
   else {  
      host = get_cix_server_host (args,0); 
      port = get_cix_server_port (args,1);
   } 
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line); 
         if (cin.eof()) throw cix_exit(); 
         if (SIGINT_throw_cix_exit) throw cix_exit();
         vector<string> vec;
         size_t finish = 0;
         for (;;){
            size_t begin = line.find_first_not_of(" \t", finish); 
            if (begin == string::npos) break; 
            finish = line.find_first_of(" \t", begin); 
            vec.push_back(line.substr(begin, finish - begin));
         }
         if(vec.size() == 0) {
            continue; 
         }
         if (cin.eof()) throw cix_exit();
         log << "command " << line << endl;
         const auto& itor = command_map.find (line);
         cix_command cmd = itor == command_map.end()
                         ? CIX_ERROR : itor->second;
         switch (cmd) {
            case CIX_EXIT:
               throw cix_exit();
               break;
            case CIX_PUT: 
               if(vec.size() < 2){ 
                  cout << "Usage: put filename" << endl;//catch errors
                  break;
               }
               cix_get (server, vec[1]);
               break;
            case CIX_GET:
               if(vec.size() < 2){
                  cout << "Usage: get filename" << endl; //catch errors
                     break;
               }
               cix_get (server, vec[1]);
               break; 
            case CIX_RM:
              if(vec.size() < 2){
                  cout << "Usage(): rm filename" << endl;
                  break;
                }
                cix_rm (server, vec[1]);
                break;
            case CIX_HELP:
               cix_help();
               break;
            case CIX_LS:
               cix_ls (server);
               break;
            default:
               log << line << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}

