#include <stdlib.h>

#include "List.h"

// the node object was type-defined in the .c file to maintain 
// its status as a private object as in the java implementation

// this reads that node is a pointer to a nodeObj
typedef struct nodeObj* node;

struct nodeObj {
  int data;
  node prev;
  node next;
};

// struct of type ListObj
typedef struct ListObj {
  node cursor;
  node front;
  node back;
  int length;
  int index;
} ListObj;

// constructor for a new list
List newList() {
  List lone = malloc (sizeof(struct ListObj));
  lone->cursor = NULL;
  lone->front = NULL;
  lone->back = NULL;
  lone->length = 0;
  lone->index = -1;
  return lone;
}

// deletes the list by freeing its memory locations
void freeList (List* pL){
  if ((*pL) == NULL) {
    printf("List.c: 43: Passing Nullpointer to freeList()");
    return;
  }

  // frees the nodes in the list
  clear(*pL);

  // frees the List itself and sets it to Null
  free(*pL);
  *pL = NULL;
}

// returns the number of elements in the list
int length(List L){
  if (L == NULL){
    printf("List.c: 62: Passing Nullptr to length()");
    return -1;
  } 
  return L->length;
}

// returns the index of the cursor element or -1 if undefined
int getIndex(List L){
  if (L == NULL){
    printf("List.c : 70: Passing Nullptr to getIndex()");
    return -1;
  }
  return L->index;
}

// Returns the front element if length > 0
int front(List L){
  if (L == NULL){
    printf("List.c : 70: Passing Nullptr to front()");
    return -1;
  }
  if (L->length > 0) return L->front->data;
  return -1;
}

// Returns back element of length > 0
int back(List L){
  if (L == NULL){
    printf("List.c : 93: Passing Nullptr to back()");
    return -1;
  }
  if (L->length > 0) return L->back->data;
  return -1;
}

// Returns cursor element in the list
int getElement(List L){
  if (L == NULL){
    printf("List.c : 103: Passing Nullptr to getElement()");
    return -1;
  }
  if (L->length > 0 && L->index >=0){
    return L->cursor->data;
  }
  return -1;
}

//Returns true if the two lists are the same
int equals (List A, List B){
  if (A == NULL || B == NULL){
    printf("List.c : 112: Passing Null ptrs to equals()");
    return -1;
  }
  node right = A->front;
  node left = B->front;
  // checks if corresponding indices match
  while (right != NULL && left !=NULL){
    if(right->data != left->data) return 0;
    right = right->next;
    left = left->next;
  }
  // if either list had more elements than the other
  if(right != NULL || left != NULL) return 0;
  return 1;
}

// Re-sets the list to the empty state
void clear(List L){
  if (L == NULL){
    printf("List.c : 130: Passing null ptr to clear()");
    return;
  }
  node front = L->front;
  while (front != NULL){
    node temp = front->next;
    free(front);
    front = temp;
  }
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

// moves the cursor to the index i
void moveTo(List L, int i){
  if (L == NULL){
    printf("List.c : 146: Passiling null ptr to moveTo()");
    return;
  }
  
  L->cursor = L->front;
  L->index = i;
  if(i >= 0 && i < L->length){
    for(; i > 0; i--){
      L->cursor = L->cursor->next;
    }
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

//this operation is equivalent to moveTo(getIndex() - 1)
void movePrev(List L){
  if (L == NULL) {
    printf("List.c : 161: passing null ptr to movePrev");
    return;
  }

  if(L->index > 0 && L->index < L->length){
    L->cursor = L->cursor->prev;
    L->index--;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

//this opeartion is equivalent to moveTo(getIndex() - 1)
void moveNext(List L){
  if (L == NULL) {
    printf("List.c: 179: passing null ptr to moveNext");
    return;
  }

  if(L->index >= 0 && L->index < L->length - 1){
    L->cursor = L->cursor->next;
    L->index++;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

// prepends to the list
void prepend(List L, int data){
  if(L == NULL) {
    printf("List.c: 195: passing null ptr to prepend()");
    return;
  }

  L->length++;
  // creates a new node
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = NULL;
  node->next = L->front;
  // checks prepending conditions
  if (L->front == NULL){
    L->back = node;
  } else {
    L->front->prev = node;
  }  
  L->front = node;

  if (L->index >= 0) L->index++;
}

//appends to the list
void append(List L, int data){
  if(L == NULL){
    printf("List.c: 215: passing null ptr to append()");
    return;
  }
  // creates a new node
  L->length++;
  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->back;
  node->next = NULL;
  // checks prepending conditions
  if(L->back == NULL){
    L->front = node;
  } else {
    L->back->next = node;
  }
  L->back = node;
}

// inserts and element before the cursor
void insertBefore(List L, int data){
  if (L == NULL){
    printf("List.c: 239: passing null ptr to insertBefore()");
    return;
  }

  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;

  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->cursor->prev;
  node->next = L->cursor;
  if(node->prev != NULL){
    L->cursor->prev->next = node; 
  } else {
    L->front = node;
  }
  
  L->cursor->prev = node;
  L->index++;
}

// inserts an element after the cursor
void insertAfter(List L, int data){
  if(L == NULL){
    printf("List.c: 239: passing null ptr to insertAfter()");
    return;
  }

  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;

  node node = malloc(sizeof(struct nodeObj));
  node->data = data;
  node->prev = L->cursor;
  node->next = L->cursor->next;
  
  if(node->next != NULL){
    L->cursor->next->prev = node;
  } else {
    L->back = node;
  }

  L->cursor->next = node;
}

// deletes the front node
void deleteFront(List L){
  if(L == NULL){
    printf("List.c: 287: passing null ptr to deleteFront()");
    return;
  }

  if(L->length > 0){
    L->length--;

    if(L->index == 0) L->cursor = NULL;
    if(L->back == L->front) L->back = NULL;

    node temp = L->front;
    L->front = L->front->next;
    free(temp);
    L->front->prev = NULL;
    if(L->index != -1) L->index--;
  }
}

// deletes the back node
void deleteBack(List L){
  if(L == NULL){
    printf("List.c: 307: passing null ptr to deleteFront()");
    return;
  }

  if(L->length > 0){
    L->length--;
    if(L->index == L->length - 1){
      L->cursor = NULL;
      L->index = -1;
    }
    if(L->back == L->front){
      free(L->back);
      L->front = NULL;
      return;
    }

    node temp = L->back;
    L->back = L->back->prev;
    free(temp);
    L->back->next = NULL;
  }

}

// deletes the cursor node
void delete(List L){
  if(L == NULL){
    printf("List.c: 328: passing null ptr to delete()");
    return;
  }

  if(L->cursor == L->front){
    deleteFront(L);
  } else if (L->cursor == L->back){
    deleteBack(L);
  }

  if (L->length > 0 && L->index > 0){
    L->length--;
    node temp = L->cursor;
    L->cursor->next->prev = L->cursor->prev;
    L->cursor->prev->next = L->cursor->next;
    L->cursor = NULL;
    L->index = -1;
    free(temp);
  }
}

// prints out the list
void printList (FILE *out, List L){
  if (L == NULL){
    printf("List.c: 352 passing null List ptr to printList()");
    return;
  }
  if (out == NULL){
    printf("List.c: 355: passing null FILE ptr to printList()");
    return;
  }

  node temp = L->front;
  while (temp != L->back){
    fprintf(out, "%d ", temp->data);
    temp = temp->next;
  }
  if(temp != NULL) fprintf(out, "%d", temp->data);
  
}

// Returns a copy of the List parameter
List copyList(List L){
  if(L == NULL){
    printf("List.c: 367: passing null ptr to copy()");
    return NULL;
  }
  List copy = newList();
  for(node tmp = L->front; tmp != NULL; tmp = tmp->next){
    append(copy, tmp->data);
  }
  return copy;
}

// Returns a new List which is the concatenation of the two
List concat(List A, List B){
  if(A == NULL || B == NULL) printf("List.c : 379: null parameter");
  List linked = copyList(A);
  for(node tmp = B->front; tmp != NULL; tmp = tmp->next){
    append(linked, tmp->data);
  }
  return linked;
}
