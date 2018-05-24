// $Id: commands.cpp,v 1.16 2016-01-14 16:10:40-08 - - $

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such function");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

void fn_cat (inode_state& state, const wordvec& words){
   if (words.size() <2){
       throw command_error ("No specified file name");
   }else{
   for (unsigned  int i = 1; i <words.size(); i++){  
   }
}
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_echo (inode_state& state, const wordvec& words){
   if (words.size()<2) 
      throw command_error("No specified string");
   int katie {0};
   for (auto c : words){
   if (c == "echo"){
      continue; 
      }
   cout << c << ' '; 
   katie++;
   } 
   cout <<"\n"; 
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}

void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()>1){
      int EC_is_rigged = stoi(words.at(1)); 
      exit_status::set(EC_is_rigged); 
      throw ysh_exit(); 
   } else{ 
      throw ysh_exit(); 
   }
}

void fn_ls (inode_state& state, const wordvec& words){
   if (words.size()<2){ 
   }

   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_lsr (inode_state& state, const wordvec& words){

   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_make (inode_state& state, const wordvec& words){
   if (words.size()<2){ 
      throw command_error("No specified file name");
   }else{
   if(words.at(1).find("/") != string::npos){
      throw command_error(words.at(0)+ ": "+ words.at(1)+": "+ "No Directories");
   }
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}
}

void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr leaf {}; 
   inode_ptr root = state.getcwd();
   if (words.size()<2) {
      throw command_error("No name given"); 
   }else if (words.size()>3){
      throw command_error("Exceeded allowed args"); 
   }else { 
   //append directory and push onto stack  
}
}
void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

