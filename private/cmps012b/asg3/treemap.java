// $Id: treemap.java,v 1.13 2014-05-12 15:31:18-07 - - $
// Usman Zahid
// uzahid

import static java.lang.System.*;

class treemap <key_t extends Comparable <key_t>, value_t> {

   private class node {
      key_t key;
      value_t value;
      node left;
      node right;
      node(key_t newkey, value_t newvalue) {
         key = newkey;
         value = newvalue;
         left= null;
         right = null;
    }
   }
   private node root;

   //Prints the depth of the binary tree

   private void print_debugger(int height, key_t key, value_t value){
      for (int i = 0; i < height; ++i)
         out.printf("  ");
      out.printf("%d %s %s%n", height, key, value);
   }
//Helper function that performs a binary search, to be implemented in 
//the function get. returns value_t and null otherwise
   private value_t get_rec (node tree, key_t key){
      
      if (tree==null) return null;
      if(key.compareTo(tree.key) <0){
        //get from left tree
        return get_rec(tree.left, key);
     }else if (key.compareTo(tree.key) > 0){
        //get from right tree
        return get_rec(tree.right, key);
     }else{
        //key was found
        return tree.value;
     }
 } 
   //fcn for put that performs a binary serach for valid entry points
   private node put_rec(node tree, key_t key, value_t value){
      if (tree ==null) {
         tree = new node(key,value);
     }else if( key.compareTo(tree.key) < 0){
         tree.left = put_rec(tree.left, key, value);
     }else if (key.compareTo(tree.key) >0){
         tree.right = put_rec(tree.right, key, value);
     }else{
         tree.value = value;
     }
     return tree;
   }

   //Preforms the inorder traversal of the binary tree
   private void debug_dump_rec (node tree, int height) {
      if( tree.left !=null) debug_dump_rec(tree.left, height+1);

      print_debugger(height, tree.key, tree.value);

      if (tree.right !=null) debug_dump_rec(tree.right, height+1);
   }

   private void do_visit_rec (visitor <key_t, value_t> visit_fn,
                              node tree) {
      if(tree == null) return;
      do_visit_rec(visit_fn, tree.left);
      visit_fn.visit(tree.key, tree.value);
      do_visit_rec(visit_fn, tree.right);
   
   }

   public value_t get (key_t key) {
      value_t  result;

      result = get_rec (root, key);
      return result;
   }

   //if there is one found, swap old and new value and return old value
   //if there is not one, create a new node as a leaf, and insert the 
   //key value and return null

   public value_t put (key_t key, value_t value) {
      
      value_t result;
      result = get_rec (root,key);
      root= put_rec(root,key,value);
      return result;
   }

   public void debug_dump () {
      debug_dump_rec (root, 0);
   }

   public void do_visit (visitor <key_t, value_t> visit_fn) {
      do_visit_rec (visit_fn, root);
   }

}
   
