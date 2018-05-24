public class ListTest { 
    
    public static void main(String[] args){
        List A = new List();
        List B = new List();
   
       for (int i=1;i<=20; i++){
           A.append(i);
           B.prepend(i);
        }
        System.out.println(A);
        System.out.println(B);
      

        for (A.moveTo(0); A.getIndex()>=0; A.moveNext()){
           System.out.print(A.getElement()+" ");
        }
        System.out.println();
        for (B.moveTo(B.length()-1); B.getIndex()>=0; B.movePrev()){
           System.out.print(B.getElement()+" ");
        }
        System.out.println();
    }
 }
