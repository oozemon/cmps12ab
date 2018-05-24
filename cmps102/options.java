//usman zahid (uzahid@ucsc.edu)
//alex hoyt (adhoyt@ucsc.edu)
//
import static java.lang.System.*;

class options {
boolean insensitive;
boolean filename_only;
boolean number_lines;
boolean reverse_match;
String regex; //flags specified in cmd line
String patty = "";
String[] filenames;

options (String[] args) {
   if (args.length == 0) { 
      err.printf ("Usage: %s [-ilnv] regex [filename...]%n", 
            messages.program_name);
      exit (messages.EXIT_FAILURE);
   }
   
   regex = args[0]; //ilnv
   patty = args[1]; //unless there are no regex
   if(regex.contains("-")){
      if(regex.contains("i")) insensitive =true;
      if(regex.contains("n")) number_lines = true;
      if(regex.contains("l")) filename_only = true;
      if(regex.contains("v")) reverse_match = true;
      
  }
      else{ err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
            messages.program_name);
exit (messages.EXIT_SYNTAX);
      }
   filenames = new String[args.length - 1];
   for (int argi = 1; argi < args.length; ++argi) {
      filenames[argi - 1] = args[argi];
   }
}
}
