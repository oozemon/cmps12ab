// $Id: cix-client.cpp,v 1.7 2014-07-25 12:12:51-07 - - $
//PRATEEK BHATT
//MARVIN CORRO
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "cix_protocol.h"
#include "logstream.h"
#include "signal_action.h"
#include "sockets.h"

logstream log (cout);

unordered_map<string,cix_command> command_map {
   {"exit", CIX_EXIT },
   {"help", CIX_HELP },
   {"ls"  , CIX_LS   },
   {"get",  CIX_GET  },
   {"put",  CIX_PUT  },
   {"rm",   CIX_RM   },

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
   header.cix_command = CIX_LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.cix_command != CIX_LSOUT) {
      log << "sent CIX_LS, server did not return CIX_LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.cix_nbytes + 1];
      recv_packet (server, buffer, header.cix_nbytes);
      log << "received " << header.cix_nbytes << " bytes" << endl;
      buffer[header.cix_nbytes] = '\0';
      cout << buffer;
   }
}

void cix_get (client_socket& server, const string& cmdi) {
   cix_header header;
   header.cix_command = CIX_GET;
   strcpy(header.cix_filename, const_cast<char*>(cmdi.c_str()));
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   ///FOR THE NEXT LINE DONT KNOW IF THIS ERROR CHECK IS HUNDRED PERCENT CORRECT YO!
   if(  header.cix_command != CIX_FILE )
   {
      log << "Sent GET, server did not return CIX_FILE" << endl;
      log << "Server returned: " << header << endl;
   }else{
      char buff[header.cix_nbytes+1];
      recv_packet(server, buff, header.cix_nbytes);
      log<< "Received: "<< header.cix_nbytes<< " Bytes"<< endl;
      buff[header.cix_nbytes] = '\0';
      //KINDA SKETCHED OUT BY IF IM WRITING IT CORRECTLY
      //DONT KNOW IF IM DOING Fstream CORRECTLY
      ofstream outWrite( header.cix_filename, ios::binary );
      outWrite.write(buff, header.cix_nbytes);
      outWrite.close();
   }
}

void cix_put (client_socket& server, const string& cmdi) {
   cix_header header;
   header.cix_command = CIX_PUT;
   strcpy (header.cix_filename, const_cast<char*> (cmdi.c_str()));
   //DONT KNOW IF IM IMPLEMENTING THIS CORRECT MIGHT GET ERRORS HERE
   ifstream ifile (cmdi);
   if(ifile.fail()){
      log << "Failed"<< endl;
      header.cix_command = CIX_NAK;
      header.cix_nbytes = errno;
      send_packet (server, &header, sizeof header);
      log << "Failure reported"<< endl;
      }else{
      ifile.seekg(0, ifile.end);
      streamsize sz = ifile.tellg();
      ifile.seekg(0, ifile.beg);
      char* buff = new char[sz];
      ifile.read(buff, sz);
      header.cix_nbytes = sz;
      send_packet(server, &header, sizeof header);
      send_packet(server, buff, header.cix_nbytes);
      log<< "Sent header"<<header<< endl;
      recv_packet(server, &header, sizeof header);
      recv_packet(server, buff, header.cix_nbytes);
      log<< "Got Response: "<< header<< "transferred"<< endl;
      ifile.close();
   }
}

void cix_rm (client_socket& server, const string& cmdi) {
   cix_header header;
   header.cix_command = CIX_RM;
   strcpy(header.cix_filename,  const_cast<char*> ( cmdi.c_str() ));
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if(header.cix_command != CIX_ACK){
      log<< "SENT CIX_RM, SERVER DID NOT REPLY CIX_ACK"<<endl;
      log<< "SERVER RETURNED: "<< header<< endl;
      cerr<< cmdi<<": "<< "Unable to be removed. Lets fix it doe."<<endl;
   }else{
      cout<< cmdi<< ": "<< "REMOVED SUCCESSFULLY :)"<< endl;
   }
 }

void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

bool SIGINT_throw_cix_exit {false};
void signal_handler (int signal) {
   log << "signal_handler: caught " << strsignal (signal) << endl;
   switch (signal) {
      case SIGINT: case SIGTERM: SIGINT_throw_cix_exit = true; break;
      default: break;
   }
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   signal_action (SIGINT, signal_handler);
   signal_action (SIGTERM, signal_handler);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) 
      {
         string line;
         string findMe;
         size_t index;
         getline (cin, line);
         index = line.find_first_of(" ");
         if (cin.eof()) 
            throw cix_exit();
         if (SIGINT_throw_cix_exit) 
            throw cix_exit();
         
         if( index != string::npos )
         {
            findMe = line.substr(++index);
            line = line.substr( 0, index-1 );
         }

         log << "command " << line << endl;
         const auto& itor = command_map.find (line);
         cix_command cmd = itor == command_map.end()
                         ? CIX_ERROR : itor->second;
         switch (cmd) {
            case CIX_EXIT:
               throw cix_exit();
               break;
            case CIX_HELP:
               cix_help();
               break;
            case CIX_LS:
               cix_ls (server);
               break;
            case CIX_GET:
               cix_get(server, findMe);
               break;
            case CIX_PUT:
               cix_put(server, findMe);
               break;
            case CIX_RM:
               cix_rm(server, findMe);
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
