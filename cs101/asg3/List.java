//Usman Zahid
//uzahid
//pa3

class List {
    private class node {
	Object data;
	node prev;
	node next;

	node(Object num){
	    data = num;
	    prev = null;
	    next = null;
	}

	// inserting a new node
	node(Object num, node previous, node after){
	    data = num;
	    prev = previous;
	    next = after;
	}
	// to string method
	public String toString(){
	    return "" + data;
	}
    }
    private static final node OFF = null;
    private node cursor;
    private node front;
    private node back;
    private int length;
    
    // Creates a new empty list
    public List (){
	cursor = OFF;
	front = null;
	back = null;
	length = 0;
    }

    // Returns number of elements in list
    public int length() {
	return length;
    }

    public int getIndex(){
	int index = -1;
	if (cursor == OFF) return index;
	for (node tmp = front; tmp != null; tmp = tmp.next){
	    index++;
	    if (tmp == cursor) break;
	}
	return index;   
    }
    
    // Returns front element if length > 0
    public Object front() {
	if (length() > 0) {
	    return front.data;
	} 
	  
	return null;
    }

    // Returns back element if length > 0
    public Object back() {
	if (length() > 0){
	    return back.data;
	}

	return null;
    }
    
    // Returns cursor element in this list
    public Object getElement(){
	if (length() > 0 && getIndex() >= 0) return cursor.data;
	return null;
    }

    //Returns true if this List and L are same integer sequence
    public boolean equals(Object L){
	if (L == null || !(L instanceof List)) {
	    System.out.println("List:equals: incorrect parameter type");
	    return false;
	}
	node right = front;
	node left = ((List)L).front;
	while (right != null && left != null){
	    if (!(right.data.equals(left.data))){
		return false;
	    }
	    right = right.next;
	    left = left.next;
	}
	// if either list had more elements than the other
	if (right != null || left != null) return false;
	return true;
    }
    //clears list
    public void clear(){
	cursor = OFF;
	front = null;
	back = null;
	length = 0;
    }
    //moves cursor
    public void moveTo(int i){
	if (i >= 0 && i <= length() - 1){
	    cursor = front;
	    for(; i > 0; i--) cursor = cursor.next;
	} else {
	    cursor = OFF;
	}
    }
    
    public void movePrev(){
	int index = getIndex();
	if (index > 0 && index <= length() - 1){
	    cursor = cursor.prev;
	} else {
	    cursor = OFF;
	}
    }
    public void moveNext(){
	int index = getIndex();
	if(index >= 0 && index < length() - 1){
	    cursor = cursor.next;
	} else {
	    cursor = OFF;
	}
    }
    
    public void prepend(Object data){
	length++;
	node node = new node(data,null, front);
	if (front != null) {
	    front.prev = node;
	} else {
	    back = node;
	}
	front = node;
    }
    public void append(Object data){
	length++;
	node t = new node(data, back, null);
	if (back != null)  back.next = t;
         else {
	    front = t;
	}
	back = t;
    }

    public void insertBefore(Object data){
	if (!(length() >0 && getIndex() >=0)) return;
	length++;
	node t = new node(data, cursor.prev, cursor);
	if (cursor.prev != null) {
	    cursor.prev.next = t;
	} else {
	    front = t;
	}

	cursor.prev = t;
    }
    
    public void insertAfter(Object data){
	if(!(length() >0 && getIndex() >=0)) return;
	length++;
	node temp = new node(data, cursor, cursor.next);
	if (cursor.next != null){
	    cursor.next.prev = temp;
	} else {
	    back = temp;
	}

	cursor.next = temp;
    }
    public void deleteFront(){
	if (length() > 0) {
	    length--;
	    if(cursor == front) cursor = OFF;
	    front = front.next;
	    front.prev = null;
	}
    }
    public void deleteBack(){
	if (length() > 0){
	    length--;
	    if(cursor == back) cursor = OFF;
	    back = back.prev;
	    back.next = null;
	}
    }
    public void delete(){	
	if (cursor == front){
	    deleteFront();
	} else if (cursor == back){
	    deleteBack();
	}
	
	if (length() > 0 && getIndex() > 0){
	    length--;
	    cursor.next.prev = cursor.prev;
	    cursor.prev.next = cursor.next;
	    cursor = OFF;
	}
	
    }
//classic toString function
    public String toString() {
	String s = "";
	node t = front;
	while (t.next != null){
	    s += t + " ";
	    t = t.next;
	}
	s += t;
	return s;
    }

}
