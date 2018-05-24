// usman zahid (uzahid@ucsc.edu)
// alex hoyt (adhoyt@ucsc.edu)


import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;
//boolean banana = false;

class jgrep {

   static void scanfile (Scanner input, String filename,
         Pattern pattern, options opts) {
       int lineno =0;
      while (input.hasNextLine()) {
         String line = input.nextLine();
         lineno++;
         boolean matches = pattern.matcher (line).find();
         boolean doAnyways = false;
         //true if can find in NEXTLINE
         if(opts.reverse_match){
              doAnyways = true;
              matches=false;
           } 
           
         if (matches) {
            if(opts.filename_only){
               out.printf ("%s\n", filename);
               //if filename boolean true then print once and break
               break;
            } //still do this if reverse == true
            if(opts.number_lines){
               out.printf ("%d %s\n",lineno,line );
               //if lineno boolean true then print once and break
               break;
            }
            out.printf ("%s:%s%n", filename, line);
         } 
         if(doAnyways){
            if(opts.filename_only){
               out.printf("%s\n", filename);
               break;
            }
            if(opts.number_lines){
               out.printf ("%d %s\n",lineno, line);
               break;
            }
            out.printf("%s:%s%n", filename, line);
         }

      }
   }
   public static void main (String[] args) {
      
     Pattern pattern;
      
      options opts = new options (args);
      //holds our first option inlv
      try {
         //opts.regex = flags 
        if(opts.insensitive ==true){
           pattern = Pattern.compile (opts.regex,
                 Pattern.CASE_INSENSITIVE);

           
        }else{
         pattern = Pattern.compile (opts.patty);
        }
         if (opts.filenames.length == 0) {
            scanfile (new Scanner (in), "<stdin>", pattern, opts);
         }else {
            for (int argi = 1; argi < opts.filenames.length; ++argi) {
               try {
                  String filename = opts.filenames[argi];
                  Scanner input = new Scanner (new File (filename));
                  scanfile (input, filename, pattern, opts);
                  input.close();
               }catch (IOException error) {
                  messages.warn (error.getMessage());
               }
            }
         }
      }catch (PatternSyntaxException error) {
         messages.die (error.getMessage());
      }
      exit (messages.exit_status);
   }

}
