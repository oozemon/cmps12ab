import java.util.*;
import java.io.*;
class AnagramPuzzleGenerator {
    public static void main(String[] args) throws FileNotFoundException {
	Scanner in = new Scanner(new FileInputStream(args[0]));

	Random rand = new Random();

	
	StringBuffer msb2 = new StringBuffer();
	StringBuffer msb;
	int R = rand.nextInt(49);
	int size = in.nextInt();//first item is the number of words	
	int i = 0;
	String st = new String();
	while ( i <= R ){
		st = new String(in.next());
		i++;
	}
	
	msb = new StringBuffer(st);
	
	int L = msb.length();
	
	char c;//char used to transfer the letters
	
	while ( L > 0 ) {
	
		int T = rand.nextInt(L);//Random number out of the total number of letters in the word
		c = msb.charAt(T);
		msb2.append(c);
		msb.deleteCharAt(T);
		L = L-1;
	}
	System.out.println(msb2);
	
	
	
	
	

    }
}
