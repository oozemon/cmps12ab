public class MatrixTest{
    public static void main(String[] args){
	int i, j, n=100000;
	Matrix A = new Matrix(n);
	Matrix B = new Matrix(n);
	A.changeEntry(1,1,1); B.changeEntry(1,1,1);
	A.changeEntry(1,2,2); B.changeEntry(1,2,0);
	A.changeEntry(1,3,3); B.changeEntry(1,3,1);
	A.changeEntry(2,1,4); B.changeEntry(2,1,0);
	A.changeEntry(2,2,5); B.changeEntry(2,2,1);
	A.changeEntry(2,3,6); B.changeEntry(2,3,0);
	A.changeEntry(3,1,7); B.changeEntry(3,1,1);
	A.changeEntry(3,2,8); B.changeEntry(3,2,1);
	A.changeEntry(3,3,9); B.changeEntry(3,3,1);

	System.out.println(A.getNNZ());
	System.out.println(A);

	System.out.println(B.getNNZ());
	System.out.println(B);

	Matrix C = A.scalarMult(1.5);
	System.out.println(C.getNNZ());
	System.out.println(C);

	Matrix D = A.add(A);
	System.out.println(D.getNNZ());
	System.out.println(D);

	Matrix E = A.sub(A);
	System.out.println(E.getNNZ());
	System.out.println(E);

	Matrix F = B.transpose();
	System.out.println(F.getNNZ());
	System.out.println(F);

	Matrix G = B.mult(B);
	System.out.println(G.getNNZ());
	System.out.println(G);

	Matrix H = A.copy();
	System.out.println(H.getNNZ());
	System.out.println(H);
	System.out.println(A.equals(H));
	System.out.println(A.equals(B));
	System.out.println(A.equals(A));

	A.makeZero();
	System.out.println(A.getNNZ());
	System.out.println(A);
	A  = H.copy();
	System.out.println("A has " + A.getNNZ() + " non-zero entries:");
	System.out.println(A);

	System.out.println("B has " + B.getNNZ() + " non-zero entries:");
	System.out.println(B);

	C = A.scalarMult(5);
	System.out.println("C = (5)*A has " + C.getNNZ() + " non-zero entries:");
	System.out.println(C);
    }
}
