// $Id: queue.java,v 1.2 2014-05-12 13:31:49-07 - - $
// Usman Zahid
// uzahid

import java.util.Iterator;
import java.util.NoSuchElementException;

class queue <item_t> implements Iterable <item_t> {

   private class node {
      item_t item;
      node link;
   }
   private node head = null;
   private node tail = null;

   public boolean isempty () {
      return(head==null);
   }

   public void insert (item_t newitem) {
      node t = new node();
      t.item = newitem;
      t.link = null;

      if(head==null){
         head = t;
         tail = t;
     }else{
         tail.link = t;
         tail = t;
     }

   }

   public Iterator <item_t> iterator () {
      return new itor ();
   }

   class itor implements Iterator <item_t> {
      node next = head;
      public boolean hasNext () {
         return next != null;
      }
      public item_t next () {
         if (! hasNext ()) throw new NoSuchElementException ();
         item_t result = next.item;
         next = next.link;
         return result;
      }
      public void remove () {
         throw new UnsupportedOperationException ();
      }
   }

}
