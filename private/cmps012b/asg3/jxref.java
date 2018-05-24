// $Id: jxref.java,v 1.88 2014-05-20 22:31:35-07 - - $
// Usman Zahid
// uzahid
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jxref {

   static final String STDIN_NAME = "-";
   static boolean treedump = false;
   static boolean caseignore = false;

   private static void printborder() {
      int i = 0;
      for(; i <72; ++i){
         out.printf(":");
   }
   }

   private static void printname(String filename) {
      out.printf("%n");
      printborder();
      out.printf("%n");
      out.printf("%s%n", filename);
      printborder();
      out.printf("%n");
      out.printf("%n");
  }

   static class printer implements visitor <String, queue <Integer>> {
      public void visit (String key, queue <Integer> value) {
         out.printf ("%s", key);
         for (int linenr: value) out.printf (" %d", linenr);
         out.printf ("%n");
      }
   }

   //Determines the command line arguments filename or command

   static boolean commandline(String arg) {
      if (arg.charAt(0) == '-' && arg.length() >1)
         return true;
      else
         return false;
   }

   static void xref_file (String filename, Scanner scan) {
      
      printname(filename);
        
      treemap <String, queue <Integer>> map =
            new treemap <String, queue <Integer>> ();

      for (int linenr = 1; scan.hasNextLine (); ++linenr) {
         for (String word: scan.nextLine().split ("\\W+")) {
            if (word.matches ("^\\d*$")) continue;
            if (caseignore == true) word = word.toLowerCase();
       //       debug text
       //       out.printf ("%s %d%n", word, linenr);
            queue<Integer> tqueue;
            tqueue = map.get(word);
            if (tqueue==null){
               queue<Integer> newqueue = new queue<Integer>();
               newqueue.insert(linenr);
               map.put(word, newqueue);
           } else{
               tqueue.insert(linenr);
         }
        }
      }
       // boolean checks
      if (treedump==true){
         map.debug_dump();
     }else {
      visitor <String, queue <Integer>> print_fn = new printer ();
      map.do_visit (print_fn);
   }
 }
   public static void main (String[] args) {
     //boolean check for args[0]
     if ((args.length != 0) && commandline(args[0]))
          bootrigger(args[0]);
      if (args.length == 0) {
         xref_file (STDIN_NAME, new Scanner (in));
      }else if (args.length == 1 && commandline(args[0])){
         xref_file (STDIN_NAME, new Scanner(in));
      }else {                                    
         for (int argi = 0; argi < args.length; ++argi) {
            String filename = args[argi]; 
            if (filename.equals (STDIN_NAME)) {
               xref_file (STDIN_NAME, new Scanner (in)); 
            }else {                                     
               try {
                  Scanner scan = new Scanner (new File (filename));
                  xref_file (filename, scan);
                  scan.close ();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage ());
               }
            }
         }
      }
      auxlib.exit (); //exit status of auxlib.java
   }


   static void bootrigger (String argument_zero){
     int i = 1;
     int l = argument_zero.length();
     for(;i<l;++i){
         switch(argument_zero.charAt(i)) {
            case 'd':
               treedump = true;
               break;
            case 'f':
               caseignore = true;
               break;
            default:
               auxlib.warn("invalid command",argument_zero.charAt(i));
               break;
            }
        }
    }
}

