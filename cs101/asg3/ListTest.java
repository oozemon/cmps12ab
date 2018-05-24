//usman zahid
//uzahid 
//pa3


public class ListTest{
    static class Entry{
	int column;
	double value;
	Entry(int col, double val){
	    column = col;
	    value = val;
	}

	public boolean equals(Object object){
	    if (object == null || !(object instanceof Entry)) {
		return false;
	    }
	    return (((Entry)object).value == value);
	}

	public String toString(){
	    return "" + column;
	}
    }

    public static void main(String[] args){
	List A = new List();
	List C = new List();
	List B = new List();
      
	for(int i=1; i<=20; i++){
	    A.append(new Entry(i, (double)i));
	    C.append(new Entry(i, (double)i));
	    B.prepend(new Entry(i, (double)i));
	}
	System.out.println(A);
	System.out.println(B);
      
	for(A.moveTo(0); A.getIndex()>=0; A.moveNext()){
	    System.out.print(A.getElement()+" ");
	}
	System.out.println();
	for(B.moveTo(B.length()-1); B.getIndex()>=0; B.movePrev()){
	    System.out.print(B.getElement()+" ");
	}

	System.out.println();
	
	System.out.println(A.equals(B));
	System.out.println(B.equals(C));
	System.out.println(C.equals(A));
	A.moveTo(5);
	A.insertBefore(-1);
	A.moveTo(15);
	A.insertAfter(-2);
	A.moveTo(10);
	A.delete();
	System.out.println(A);
	A.clear();
	System.out.println(A.length());
    }
}

// Output of this program:
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// false
// false
// true
// 1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
// 0
