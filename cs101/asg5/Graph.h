//usman zahid
//uzahid
//pa5

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"
#define UNDEF -255
#define NIL 0

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 
// returns newGraph
Graph newGraph(int n); 
// frees memory
void freeGraph(Graph* pG); 
/*** Access functions ***/ 
// returns vertices in G
int getOrder(Graph G); 
//  returns size
int getSize(Graph G);
// return the parent of vertex u in the DFS tree
// or NIL if DFS() has not yet been called
// Pre : 1 <= U <= getOrder(G)
int getParent(Graph G, int u); 
// Pre : 1 <= U <= getOrder(G)
int getDiscover(Graph G, int u); 
// Pre : 1 <= U <= getOrder()
int getFinish(Graph G, int u); 

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v); 
void DFS(Graph G, List s); 
void printGraph(FILE* out, Graph G); 
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif
