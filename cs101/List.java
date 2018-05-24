class List{
   private class Node{
		int data; 
		Node next;
                Node prev; 
		Node (int dat){
			data = dat;
			next = null;
                        prev = null;
		}
		public String toString(){ 
			return String.valueOf(data);
		}
	}
	//Fields
		private Node front;
		private Node back;
                private Node cursor;
		private int length;
                private int index;		
	// Constructor
	List() {cursor = front = back = null; length = 0; index= -1;}
	// Creates a new empty list.
	// Access functions 	
	int length(){  // Returns number of elements in this list.
	   return length;
	}
	int getIndex(){
/*            if (cursor==null){
              return 0;
           }
           Node tmp=front;
           for(index=1; index<length;index++){
              if(tmp==cursor){
                 return index; }
              else { tmp=tmp.next; }
           }*/
           return index;
        }
           // Returns the index of the cursor element in this list, or 
	 // returns -1 if the cursor element is undefined.
	
	int front(){
		if(length<0){
			throw new RuntimeException("Queso Error");// Returns front element in this list. Pre: length()>0
		}
		return front.data;
	}
	
	int back(){
              if(length()<0){
                 throw new RuntimeException("Function back has called empty list");
              }
              return back.data;
             }// Returns back element in this List. Pre: length()>0
	
	int getElement(){
             
             if ( length() > 0 && getIndex() >= 0){
                return cursor.data;
             }
     	     return -1;
             }
      
          // Returns cursor element in this list. 
	 // Pre: length()>0, getIndex()>=0
	
	boolean equals(List L){ 
		Node n = front;
		Node m = L.front;
                while (n != null && m != null){
                   if(n.data != m.data){
                     return false;
	       }
               n = n.next;
               m = m.next;
	    }
              return true;
       } 
		// Returns true if this List and L are the same integer
	
	 // sequence. The cursor is ignored in both lists.
	// Manipulation procedures 
	
	void clear(){
           this.front = null;
           this.back = null; 
           this.cursor= null;
           length = 0;
        } // Re-sets this List to the empty state.
	
	void moveTo(int i){ 
           if (i >= 0 && i <= (length() -1)){
                 index = 0;
                 cursor = front;
                 while(index !=i) {
                    cursor= cursor.next;
                    index++;
                 }
           }
           else { 
             index = -1;
             cursor = null;
          }
         }
         // If 0<=i<=length()-1, moves the cursor to the element 
	 // at index i, otherwise the cursor becomes undefined.
	
	void movePrev(){
           if(0<getIndex() && getIndex() <= length() -1){
              cursor = cursor.prev;
              index--;
            }
            else {
                index = -1;
                cursor = null;
            }
         }
         // If 0<getIndex()<=length()-1, moves the cursor one step toward the
	 // front of the list. If getIndex()==0, cursor becomes undefined. 
	 // If getIndex()==-1, cursor remains undefined. This operation is
	 // equivalent to moveTo(getIndex()-1).
	
	void moveNext(){ 
           if(getIndex()>=0 && getIndex() < length() -1){
              cursor = cursor.next;
              index++;
           } else{
             index = -1;
             cursor = null;}
          }
                 //cursor 
            // If 0<=getIndex()<length()-1, moves the cursor one step toward the
	 // back of the list. If getIndex()==length()-1, cursor becomes
	 // undefined. If index==-1, cursor remains undefined. This
	 // operation is equivalent to moveTo(getIndex()+1).
	
	void prepend(int data){ 
                Node node = new Node(data);
                if (length==0){
                   front = back = node;
                    length++;
                }
                else{
                   front.prev = node;
                   node.next = front;
                   front = node; 
                   length++;
                }
           }// Inserts new element before front element in this List.
	
	void append(int data){
		Node node = new Node(data);
		if(length==0) {front = back = node;}
		else {back.next = node; back = node;}
		length++;// Inserts new element after back element in this List.
	}
	
	void insertBefore(int data){
           if (length()<0){
              throw new RuntimeException("Queue Error insterbefore");
           }
           if (getIndex()<=0){
              throw new RuntimeException("Queue Error insertbefore2dbg");
           }
           Node node = new Node(data);
           if (cursor.prev==null){
              node.next=front;
              front.prev = node;
              front = node;
           }else{
              node.prev=cursor.prev;
              node.next=cursor;
              cursor.prev.next=node;
              cursor.prev=node;
           }
           length++;
       }       
          
          
          // Inserts new element before cursor element in this
	  // List. Pre: length()>0, getIndex()>=0
	
	void insertAfter(int data){
              if (length()<0){
                 throw new RuntimeException("Queue Error insertafter");
           }
              if (getIndex()<=0){
                 throw new RuntimeException("Queue Error insterafter2dbg");
           }
              Node node = new Node(data);
              if (cursor.next ==null){
                 back.next = node;
                 back = node;
                 back.prev = cursor;
             }else{
                 node.prev = cursor;
                 node.next = cursor.next;
                 cursor.next.prev = node;
                 cursor.next = node;
           }
           length++;
       }

               // Inserts new element after cursor element in this 
	 // List. Pre: length()>0, getIndex()>=0
	
	void deleteFront(){
           if (length() > 0){
             length--;
           if (cursor==front){
              cursor = null;
           }
              front = front.next;
              front.prev=null;
           }
        }
            // Deletes the front element in this List. Pre: length()>0
	
	void deleteBack(){
          /* if(length==0){
              throw new RuntimeException("Queue Error");
           }*/
           if ( length()>0){
              length--;
              if (cursor == back){ 
                 cursor = null;
              }
              back = back.prev;
              back.next = null;
           }
        } // Deletes the back element in this List. Pre: length()>0
	
	void delete(){
       /*      if (cursor == front){
                deleteFront();
            }else if (cursor == back){
                deleteBack();
            }
            if (length() >0 && getIndex() >0){
               length--;
               cursor.next.prev = cursor.prev;
               cursor.prev.next = cursor.next;
               cursor = null;
           }
        }
          
         */
           if(length()<0){
              throw new RuntimeException("delete is messed up bruh");
           }
           if (getIndex()<=0){
              throw new RuntimeException("2delete is messed");
           }
           if (this.length >1){
              if(cursor.prev==null){
                 front = cursor.next;
                 cursor.next = null;
              }
              else  if (cursor.next == null){ 
                 back = cursor.prev;
                 cursor.prev = null;
              }else {
                 cursor.prev.next = cursor.next;
                 cursor.next.prev= cursor.prev;
                 cursor.prev = cursor.next = null;
              }
              cursor= null;
           }
           else {front = back = cursor = null;}
           length--;
         }
            // Deletes cursor element in this List. Cursor is undefined after this 
	 // operation. Pre: length()>0, getIndex()>=0
	// Other methods 
	
	public String toString(){
		String str = "";
		for(Node n=front; n!=null; n=n.next){
			str += n.toString() + " ";
	// Overides Object's toString method. Creates a string 
		}
		return str;
	}
	 // consisting of a space separated sequence of integers
	 // with front on the left and back on the right. The
	// cursor is ignored.
	
	List copy(){
		List L = new List();
		Node n = front;
		while (n!=null){
			L.append(n.data);
			n = n.next;// Returns a new list representing the same integer sequence as this
		}
		return L;
	}
}
	
 // list. The cursor in the new list is undefined, regardless of the     	 // state of the cursor in this List. This List is unchanged.
