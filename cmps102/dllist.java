// $Id: dllist.java,v 1.3 2014-04-27 15:26:38-07 - - $

class dllist {

   public enum position {FIRST, PREVIOUS, FOLLOWING, LAST};

   private class node {
      String item;
      node prev;
      node next;
   }

   private node first = null;
   private node current = null;
   private node last = null;
   private int currentposition = 0;

   public void setposition (position pos) {
    //position pos = new position;
    //for (int i = 0; pos<node.length; i++){
      //move the current position of the link to be of the 
      //the first or last position in the list, or the node immediately
      //precious to or immediately following the current position
      //an attempt to move before the first or after the last position
      //is silently ignored.
      //}      
  //    currentposition = pos;
      
   }

   public boolean isempty () {
      throw new UnsupportedOperationException();
   }

   public String getitem () {
      throw new UnsupportedOperationException();
   }

   public int getposition () {
      throw new UnsupportedOperationException();
   }

   public void delete () {
      throw new UnsupportedOperationException();
   }

   public void insert (String item, position pos) {
      throw new UnsupportedOperationException();
   }

}

