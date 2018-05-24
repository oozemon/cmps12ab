#include <stdlib.h>

#include "Graph.h"

static void insertsort(List L, int u);

#define WHITE 10000001
#define BLACK 19999991
#define GRAY  -6666669
struct GraphObj {
  List *array;
  int *colors;
  int *parents;
  int *discover;
  int *finish;
  int order; // number of vertices
  int size; // number of edges
};



//Returns a Graph pointing to a newly created GraphObj
//representing a graph with n vertices and no edges
Graph newGraph(int n){ 
  Graph new = malloc(sizeof(struct GraphObj)); 
  new->array = calloc (n + 1, sizeof(List)); 
  new->colors = calloc(n + 1, sizeof(int)); 
  new->parents = calloc(n + 1, sizeof(int)); 
  new->discover = calloc(n + 1, sizeof(int));
  new->finish = calloc(n+1, sizeof(int));
  new->order = n; // n vertices
  new->size = 0; // no edges
  for (int i = 0; i < n + 1; i++){
    new->array[i] = newList();
    new->colors[i] = WHITE;
    new->parents[i] = NIL; // no parents as of yet
    new->discover[i] = UNDEF; // none have been discovered
    new->finish[i] = UNDEF; // none have been finished
  }
  return new;
} 
// frees all dynamic memory associated with Graph 
void freeGraph(Graph* pG){
  Graph freed = *pG; 
  if(freed == NULL){
    printf("freeGraph:Can't free a null graph\n");
    return;
  }
  for(int i = 0; i < (freed->order) + 1; i++){
    freeList(&(freed->array[i]));
  }
  free(freed->array); 
  free(freed->colors); 
  free(freed->parents); 
  free(freed->discover);
  free(freed->finish);
  free(*pG);
  *pG = NULL; 
} 

 

/*** Access functions ***/
// returns the number of vertices
int getOrder(Graph G){
  if(G == NULL) {
    printf("getOrder:passed in a null graph\n");
    return UNDEF;
  }
  return G->order;
}
// returns the number of edges
int getSize(Graph G){
  return G->size;
}
// returns the parent vertex of the chosen vertex
int getParent(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getParent: invalid u parameter\n");
    return 0;
  }
  return G->parents[u];
}

// returns the discover time of the vertex from source 
int getDiscover(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getDiscover: invalid u parameter\n");
    return 0;
  }
  return G->discover[u];
}
 
// returns the finish time of the vertex from the source
int getFinish(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getFinish: invalid u parameter\n");
    return 0;
  }
  return G->finish[u];
} 

// creates an edge between vertices
// precondition, the vertex numbers must be > 1 and < getOrder(G) 
void addEdge(Graph G, int u, int v){
  if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Addedge: preconditions not met\n");
    printf("%d %d\n", u, v);
    return;
  }
  List U = G->array[u];
  List V = G->array[v];
  insertsort(U, v);
  insertsort(V, u);
}

// private function to append vertices in adjacency list in order
static void insertsort(List L, int u){
  if (length(L) == 0){
    append(L, u);
    return;
  }
  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)){
    int big = getElement(L);
    if(u < big){
      insertBefore(L, u);
      break;
    }
  }
  if(getIndex(L) == -1){
    append(L, u);
  }
}
 
// adds a directed edge
void addArc(Graph G, int u, int v){
  if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Addarc: preconditions not met\n");
    printf("%d %d\n", u, v);
    return;
  }
  List U = G->array[u];
  insertsort(U, v);
}
 
// DFS algorithm
void DFS(Graph G, List s){
  if(length(s) != getOrder(G)){
    printf("DFS: unequal list and graph sizes\n");
    return;
  }
  int time = 0;
  int size = length(s);
  void Visit(int vertex){
    time = time + 1;
    G->discover[vertex] = time;
    G->colors[vertex] = GRAY;
    List adj = G->array[vertex];
    for(moveTo(adj, 0); getIndex(adj) >=0; moveNext(adj)){
      int vert = getElement(adj);
      if(G->colors[vert] == WHITE){
	G->parents[vert] = vertex;
	Visit(vert);
      }
      
    }
    G->colors[vertex] = BLACK;
    time = time +1;
    G->finish[vertex] = time;
    prepend(s, vertex);
  }

  for(moveTo(s, 0); getIndex(s) >=0; moveNext(s)){
    int vertex = getElement(s);
    G->colors[vertex] = WHITE;
    G->parents[vertex] = NIL;
  }

  for(moveTo(s, 0); getIndex(s) >=0; moveNext(s)){
    int vertex = getElement(s);
    if(G->colors[vertex] == WHITE) Visit(vertex);
  }
  for(;size > 0 ; size--){
    deleteBack(s);
  }
} 

/*** Other operations ***/ 
// print function to print the graph in pretty format
void printGraph(FILE* out, Graph G){
  if(out == NULL || G == NULL){
    printf("printGraph: Passed in NUll parameters\n");
    return;
  }

  for (int i = 1; i < getOrder(G) + 1; i++){
    fprintf(out, "%d: ", i);
    printList(out, G->array[i]);
    fprintf(out, "\n");
  }
}
// returns the Transpose of the graph
// The adjacency lists are reversed
Graph transpose(Graph G){
 int n = G->order;
  Graph new = malloc(sizeof(struct GraphObj)); 
  new->array = calloc (n + 1, sizeof(List)); 
  new->colors = calloc(n + 1, sizeof(int)); 
  new->parents = calloc(n + 1, sizeof(int)); 
  new->discover = calloc(n + 1, sizeof(int));
  new->finish = calloc(n+1, sizeof(int));
  new->order = G->order;
  new->size = G->size;
  for (int i = 0; i < n + 1; i++){
    new->array[i] = newList();
    new->colors[i] = WHITE;
    new->parents[i] = NIL;
    new->discover[i] = UNDEF;
    new->finish[i] = UNDEF;
  }
  // puts in the entries in transpose order
  for(int i = 0; i < n + 1; i++){
    List g = G->array[i];
    for(moveTo(g, 0); getIndex(g) >= 0; moveNext(g)){
      append(new->array[getElement(g)], i);
    }
  }
  return new;
}
// makes an indentical Graph G
Graph copyGraph(Graph G){
  int n = G->order;
  Graph new = malloc(sizeof(struct GraphObj)); 
  new->array = calloc (n + 1, sizeof(List)); 
  new->colors = calloc(n + 1, sizeof(int)); 
  new->parents = calloc(n + 1, sizeof(int)); 
  new->discover = calloc(n + 1, sizeof(int));
  new->finish = calloc(n+1, sizeof(int));
  new->order = G->order;
  new->size = G->size;
  for (int i = 0; i < n + 1; i++){
    new->array[i] = newList();
    List g = G->array[i];
    // copies over the entries
    for(moveTo(g, 0); getIndex(g) >= 0; moveNext(g)){
      append(new->array[i], getElement(g));
    }
    new->colors[i] = WHITE;
    new->parents[i] = NIL;
    new->discover[i] = UNDEF;
    new->finish[i] = UNDEF;
  }
  return new;
}
