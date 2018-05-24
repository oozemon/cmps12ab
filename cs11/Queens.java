/*Roots.java
*Usman Zahid 
*uzahid
*pa5
*finds the solutions of n-queens on an nxn board
*/
import java.util.*;

class Queens{
    static int Solutions = 0;
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int num = 4;
        int z = 0;
        boolean verbose = false;
        boolean iError = true;
        if(args.length == 1){
            try{
            num = Integer.parseInt(args[0]);
        }
        catch(NumberFormatException e){
                    System.out.println("Usage: Queens [-v] number");
                    System.out.println("Options: -v verbose output, print all solutions");
                    System.exit(1);
        }
            if (num <0){
                   System.out.println("Usage: Queens [-v] number");
                   System.out.println("Options: -v verbose output, print all solutions");
                   System.exit(1);
                }
            }else if(args.length == 2) {
            args[0] = "-v";
            try{
            num = Integer.parseInt(args[1]);
        }
        catch(NumberFormatException e){
            System.out.println("Usage: Queens [-v] number");
            System.out.println("Options: -v verbose output, print all solutions");
            System.exit(1);
        }
             if (num <0){
                   System.out.println("Usage: Queens [-v] number");
                   System.out.println("Options: -v verbose output, print all solutions");
                   System.exit(1);
                }
            verbose = true;
            
            
        }else if(args.length==0 || args.length >2){

               System.out.println("Usage: Queens [-v] number");
               System.out.println("Options: -v verbose output, print all solutions");
               System.exit(1);
                } 
        int [] A = new int[num+1];
        int l = factorial(num);
        for (int i = 0; i<num+1;i++){
            A[i]=i;
        }            
        for (int m = 0; m < l; m++){
            
            nextPermutation(A); 
            if(isSolution(A) == true){
                if (verbose == true){
                    printArray(A,num);
                }
            }
        }   
        System.out.println(num+"-Queens has "+Solutions+" solutions");
        
    }
    
    static void printArray(int[] A, int num){
        System.out.print("(");
        for(int i = 1; i < A.length; i++){
            System.out.print(A[i]);
            if(i<A.length-1){
                System.out.print(",");
            }
        }
        System.out.print(")");
        System.out.println();
    }
    
    static void nextPermutation(int[]A){
        int pivot = 0, suc = 0;
        for(int o = A.length-2; o > 0; o--){
            if(A[o] < A[o+1]){
                pivot = o;
                break;
            }
        }
        
        if(pivot == 0){
            reverse(A,1,A.length-1);
            return;
        }
        for(int o = A.length-1; o > 0; o--){
            if(A[o] > A[pivot]){
                suc = o;
                break;
            }
        }
        swap(A,pivot,suc);
        reverse(A,pivot+1,A.length-1);
    }
    
    static void reverse(int[] A, int i, int o){
        while(i < o){
            swap(A,i,o);
            i++;
            o--;
        }
    }
    
    static boolean isSolution(int[] A){
        boolean p = true;
        for(int i =1; i <A.length-1; i++){
            for(int o = i+1; o < A.length; o++){
                if(Math.abs(A[o]-A[i]) == o-i){
                    p = false;
                }
            }
        }
        if(p){
            Solutions++;
        }
        return p;
    }
    
    
    static void swap(int[] A, int i, int o){
        int temp;
        temp = A[i];
        A[i] = A[o];
        A[o] = temp;
    }
    
    static int factorial(int f){
        int x, factorial = 1;
        for(x = 1; x <=f; x++){
            factorial *= x;
        }
        return factorial;
    }
}