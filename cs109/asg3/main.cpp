#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

void trim_whitespace(string& str) {
   size_t left_index = str.find_first_not_of(" ");
   if (left_index != 0 and left_index != string::npos) {
      str = str.substr(left_index, str.size()-left_index);
   }
   size_t right_index = str.find_last_not_of(" ");
   if (right_index != str.size()-1 and right_index != string::npos) {
      str = str.substr(0, right_index+1);
   }

   if (right_index == string::npos or left_index == string::npos) {
      str = "";
   }
}

void search_by_key(str_str_map& map, const string& key) {
   str_str_map::iterator result = map.find(key);
   if (result != str_str_map::iterator()) {
      cout << result->first << " = " << result->second << endl;
   } else {
      cout << key << ": key not found" << endl;
   }
}

void search_by_value(str_str_map& map, const string& value) {
   for (str_str_map::iterator it = map.begin(); it != map.end(); ++it) {
      if (it->second == value) {
         cout << it->first << " = " << it->second << endl;
      }
   }
}

void assign_key(str_str_map& map, const string& key,
                const string& val) {
   map.insert(str_str_pair(key, val));
   cout << key << " = " << val << endl;
}

void print_map(str_str_map& map) {
   cout << map;
}

void process_line(str_str_map& map, string& line) {
   cout << line << endl;
   trim_whitespace(line);
   string key("");
   string value("");
   size_t index_of_equals = line.find_first_of("=");

      if (line.size() > 0 and line.at(0) != '#') {
      if (index_of_equals == string::npos) {
         key = line;
         search_by_key(map, line);
      } else {
         if (line.size() == 1) {
            print_map(map);
         } else if (index_of_equals == line.size()-1) {
            key = line.substr(0, index_of_equals);
         } else if (index_of_equals == 0) {
            value = line.substr(1, line.size()-1);
            search_by_value(map, value);
         } else {
            key = line.substr(0, index_of_equals);
            value = line.substr(index_of_equals+1,
            line.size());
            assign_key(map, key, value);
         }
      }
   }
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   str_str_map map;
   ifstream infile;
   bool no_files = true;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      no_files = false;
      string line;
      if (!strcmp(*argp, "=")) {
         infile.open(*argp);
         if (infile.fail()) {
            cerr << "Couldn't open file: " << *argp << endl;
            return EXIT_FAILURE;
         } else {
            int line_count = 1;
            while (getline(infile, line)) {
               cout << *argp << ": " << line_count++ << ": ";
               process_line(map, line);
            }
            infile.close();
         }
      } else {
         while (getline(cin, line)) {
            process_line(map, line);
         }
      }
      if (no_files) {
         while (getline(cin, line)) {
            process_line(map, line);
         }
      }
   }

   return EXIT_SUCCESS;
}

