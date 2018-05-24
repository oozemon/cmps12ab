//Usman Zahid
//uzahid
//pa1

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;
class Lex{
    
    static Scanner open(String filename){
	Scanner sc = null;
	try{
	    sc = new Scanner(new File(filename));
	} catch (IOException exception){
	    System.err.println("IOException error");
	    System.exit(1);
	}
	return sc;
    }
    
    public static void main (String[] args){
        int b,c = 0;
	if(args.length != 2) {
	    System.err.println("Usage: infile outfile");
	    System.exit(1);
	}
	Scanner in = open(args[0]);
        List M = new List();
	PrintWriter out = null;
	try {
	    out = new PrintWriter(new FileWriter(args[1]));
	} catch (FileNotFoundException exception){
	    System.err.println("FilenotFound error");
	    System.exit(1);
	} catch (IOException exception){
	    System.err.println("IOException error");
	   System.exit(1);
	}
	int number = countlines(in);
	in = open(args[0]);
	String[] a = read (in, number);
	List L = insertsort(a);
	for(L.moveTo(0); L.getIndex()>=0; L.moveNext()){
	    out.println(a[L.getElement()]);
	}
	out.close();
	
    }
   static String[] read(Scanner file, int lines){
	String[] a = new String[lines];
	for(int i = 0; file.hasNextLine(); i++){
	    a[i] = file.nextLine();
	}
	return a;
    }
   static int countlines(Scanner file){
	int index = 0;
	for(; file.hasNextLine(); file.nextLine()) index++;
	return index;
    }  
    static List insertsort(String[] file){	
	List L = new List();
	if (file.length > 0){
            L.append(0);
        }
	for (int i = 1; i < file.length; i++){
	    String string = file[i];
            int cursor =0;
	    int index = i - 1;
	    L.moveTo(index);
	    while (string.compareTo(file[L.getElement()]) < 1 && index > -1){	
		index--;
		L.movePrev();
                cursor++;
	    }
	    if(L.getIndex() == -1){
		L.prepend(i);
	    } else {
		L.insertAfter(i);
	    }
	}
	return L;
    } 
}

