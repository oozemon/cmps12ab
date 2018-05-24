//usman zahid 
//uzahid 
//pa3
class Matrix {
    private class Entry{
	int column;
	double value;
	Entry(int col, double val){
	    column = col;
	    value = val;
	}

	public boolean equals(Object object){
	    if(object == null || !(object instanceof Entry)){
		System.out.println("Entry:Equals: incorrect parameter type");
		return false;
	    }
	    return ((Entry)object).value == value && ((Entry)object).column == column;
	}

	public String toString(){
	    return "(" + column + ", " +  value + ")";
	}
    }

    private List[] matrix;
    private int NNZ;

    // Makes a new n X n zero Matrix. pre : n >=1
    public Matrix(int n){
	if (n < 1){
	    System.out.println("Please enter a valid matrix size");
	    return;
	}
	matrix = new List[n];
	for (int i = 0; i < n; i++) matrix[i] = new List();
	NNZ = 0;
    }

    // Returns n, the number of rows and columns of this matrix
    public int getSize(){
	return matrix.length;
    }

    // Returns the number of non-zero entries in this Matrix
    public int getNNZ(){
	return NNZ; 
    }
    
    // overrides Object's equals() method
    public boolean equals(Object x){
	// checks for correct parameters
	if (x == null || !(x instanceof Matrix)) {
	    System.out.println("Matrix:equals: incorrect parameters");
	    return false;
	}
	Matrix temp = (Matrix)x;
	// checks for equal lengths
	if(temp.getSize() != matrix.length){
	    return false;
	}
	// compares list entries
	for(int i = 0; i < matrix.length; i++){
	    if(!(matrix[i].equals(temp.matrix[i]))){
		return false;
	    }
	}
	return true;
    }
    public void makeZero(){
	// clears all the lists
	for(int i = 0; i < matrix.length; i++){
	    matrix[i].clear();
	}
	NNZ = 0;
    }
    //copy matrix
    public Matrix copy(){
	Matrix copy = new Matrix(matrix.length);
	for(int row = 0; row < matrix.length; row++){
	    List old = matrix[row];
	    List fresh = copy.matrix[row];
	    for(old.moveTo(0); old.getIndex() >= 0; old.moveNext()){
		Object object = old.getElement();
		// object type condition
		if (object == null || !(object instanceof Entry)) {
		    System.out.println("Matrix:copy: Not correct type");
		    return null;
		}
		Entry ij = (Entry)object; 
		Entry ijcopy = new Entry(ij.column, ij.value);
		fresh.append(ijcopy);
	    }
	}
	copy.NNZ = NNZ;
	return copy;
    }
    public void changeEntry(int i, int j, double x){
	if( (i + j) < 2 || (i + j) > (2 * matrix.length)){
	    System.out.println("Aarayexception out of bounds");
	    return;
	} 
	List row = matrix[i - 1];
	if(row == null) System.out.println("Row is null");
	Entry ij = null;
	// list iterator 
	for(row.moveTo(0); row.getIndex() >= 0; row.moveNext()){
	    Object object = row.getElement();
	    //checks to make sure objects in list are of type Entry
	    if (object == null || !(object instanceof Entry)) {
		System.out.println("Incorrect data type");
		return;
	    }
	    ij = (Entry)object;
	    if(ij.column < j) continue;
	    break;
	}
	if(row.getIndex() == -1 && x != 0){
	    row.append(new Entry(j, x));
	    NNZ++;
	}else if (ij != null && ij.column == j){
	    if(x == 0){
		row.delete();
		NNZ--;
	    } else {
		ij.value = x;
	    }
	} else {
	    if(x != 0){
		row.insertBefore(new Entry(j, x));
		NNZ++;
	    }
	}
	
    }

    // product of x and the matrix
    public Matrix scalarMult(double x){
	// checks to see if 0, if so, all is zero
	if(x == 0) this.makeZero();
	//iterates over the rows
	Matrix copy = new Matrix(matrix.length);
	for(int row = 0; row < matrix.length; row++){
	    List old = matrix[row];
	    List fresh = copy.matrix[row];
	    for(old.moveTo(0); old.getIndex() >= 0; old.moveNext()){
		Object object = old.getElement();
		// checks to make sure objects in list are of type Entry
		if (object == null || !(object instanceof Entry)) {
		    System.out.println("Matrix:copy: Not correct type");
		    return null;
		}
		Entry ij = (Entry)object;

		// copies over the column and value * scalar
		Entry ijcopy = new Entry(ij.column, (ij.value) * x);
		fresh.append(ijcopy);
	    }
	}
	// number of non-zero entries will be the same
	copy.NNZ = NNZ;
	return copy;
    }

    public Matrix add(Matrix M){
	if(matrix.length != M.matrix.length){
	    System.out.println("Matrix:add: different matrix sizes");
	    return null;
	}
	if(M == this) return this.scalarMult(2);
	Matrix copy = new Matrix(matrix.length);
	// loop iterates over index i which indicates the rows
	for(int i = 0; i < matrix.length; i++){
	    List one = matrix[i];
	    List two = M.matrix[i];
	    List sum = copy.matrix[i];
	    
	    // this algorithm does addition much like 
	    // the "merging" process in merge sort
	    one.moveTo(0);
	    two.moveTo(0);
	    // iterates through each list
	    while(one.getIndex() >= 0 && two.getIndex() >= 0){
		Entry r = (Entry)(one.getElement());
		Entry l = (Entry)(two.getElement());
		copy.NNZ++;
		if(r.column == l.column){
		    if(r.value + l.value != 0){
			sum.append(new Entry(r.column, r.value + l.value));
		    } else {
			NNZ--; // decrement of 0 result
		    }
		    one.moveNext();
		    two.moveNext();
		} else if (r.column < l.column){
		    sum.append(new Entry(r.column, r.value));
		    one.moveNext();
		} else {
		    sum.append(new Entry(l.column, l.value));
		    two.moveNext();
		}
	    }

	    // if both cursors are OFF then exit the loop
	    if (one.getIndex() == two.getIndex()) continue;
	    // if either cursor is still ON then append the rest
	    List rest = (one.getIndex() >= 0)? one : two;
	    while(rest.getIndex() >= 0){
		Entry fin = (Entry)(rest.getElement());
		copy.NNZ++;
		sum.append(new Entry(fin.column, fin.value));
		rest.moveNext();
	    }
	    
	}
	return copy;
    }
    public Matrix sub(Matrix M){
	if(matrix.length != M.matrix.length){
	    System.out.println("Matrix:sub: different matrix sizes");
	    return null;
	}
	// if it is the exact same matrix then return the 0 matrix
	if(M == this) return new Matrix(matrix.length);

	Matrix copy = new Matrix(matrix.length);
	//for loop that iterates over rows
	for(int row = 0; row < matrix.length; row++){
	    List l1 = matrix[row];
	    List l2 = M.matrix[row];
	    List l3 = copy.matrix[row];
	    
	    //very similar to mergeSort function
	    l1.moveTo(0);
	    l2.moveTo(0);
	    while(l1.getIndex() >= 0 && l2.getIndex() >= 0){
		Entry r = (Entry)(l1.getElement());
		Entry l = (Entry)(l2.getElement());
		copy.NNZ++;
		if(r.column == l.column){
		    if(r.value - l.value != 0){
			l3.append(new Entry(r.column, r.value - l.value));
		    } else {
			NNZ--;
		    }
		    l1.moveNext();
		    l2.moveNext();
		} else if (r.column < l.column){
		    l3.append(new Entry(r.column, r.value));
		    l1.moveNext();
		} else {
		    l3.append(new Entry(l.column, 0 - l.value));
		    l2.moveNext();
		}
	    }

	    // exit loops is both ifs are unequal
	    if (l1.getIndex() == l2.getIndex()) continue;
	    List L = (l2.getIndex() >= 0)? l1 : l2;
	    int sign = (l1.getIndex() >= 0)? 1 : -1;
	    while(L.getIndex() >= 0){
		Entry fin = (Entry)(L.getElement());
		copy.NNZ++;
		l3.append(new Entry(fin.column, sign * fin.value));
		L.moveNext();
	    }
	    
	}
	return copy;
    }
   //does matrix transpose 
    public Matrix transpose(){
	Matrix M = new Matrix(matrix.length);
	for(int i = 0; i < matrix.length; i++){
	    List col = matrix[i];
	    for(col.moveTo(0); col.getIndex() >= 0; col.moveNext()){
		Entry entry = (Entry)(col.getElement());
		int line = entry.column - 1;
		M.matrix[line].append(new Entry(i + 1, entry.value));
	    }
	}
	M.NNZ = NNZ;
	return M;
    }
    public Matrix mult(Matrix prod){
	if(matrix.length != prod.matrix.length){
	    System.out.println("Matrix:mult: invalid size parameter");
	    return null;
	}

	Matrix copy = new Matrix(matrix.length);
	if(NNZ == 0 || prod.NNZ == 0) return copy;
	Matrix trans = prod.transpose();
	for(int i = 0; i < matrix.length; i++){
	    if(matrix[i].length() == 0) continue;
	    for(int j = 0; j < matrix.length; j++){
		if(trans.matrix[j].length() == 0) continue;
		double result = dot(matrix[i] , trans.matrix[j]);
		if(result != 0){
		    copy.matrix[i].append(new Entry(j + 1, result));
		    copy.NNZ++;
		}
	    }
	}
	return copy;
	
    }

    // does dot product
    private static double dot(List one, List dos){
	double result = 0;
	one.moveTo(0);
	dos.moveTo(0);
	while(one.getIndex() >= 0 && dos.getIndex() >= 0){
	    Entry o = (Entry)(one.getElement());
	    Entry d = (Entry)(dos.getElement());
	    if(o.column == d.column){
		result += o.value * d.value;
		one.moveNext();
		dos.moveNext();
	    } else if (o.column < d.column){
		one.moveNext();
	    } else {
		dos.moveNext();
	    }
	}
	return result;
    }
    
    // to string method for Matrix
    public String toString(){
	String s = "";
	for(int i = 0; i < matrix.length; i++){
	    if(matrix[i].length() > 0){
		s += (i+1) + ": " +  matrix[i] + "\n";
	    }
	    
	}
	return s;
    }

}
