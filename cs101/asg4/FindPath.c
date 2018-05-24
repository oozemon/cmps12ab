//usman zahid
//uzahid
//pa4 
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Graph.h"
#define MAX_LEN 165

int main (int argc, char* argv[]){
  char line[MAX_LEN];
  if(argc != 3) {
    printf("Invalid input values");
    exit(1);
  }
  FILE* input = fopen(argv[1], "r");
  FILE* output = fopen(argv[2], "w");

  // checks if files have been open and or created
  if(input == NULL){ 
    printf("File  %s cammpt be read\n", argv[1]);
    return 1;
  } else if (output == NULL){
    printf("File %s cannot be read \n", argv[2]);
    return 1;
  }
  fgets(line, MAX_LEN, input);
  int numVertex = 0;
  sscanf(line, "%d", &numVertex);
  
  // new graph
  Graph gph = newGraph(numVertex);
  while( fgets(line, MAX_LEN, input) != NULL) {
    int v1 = 0;
    int v2 = 0;
    sscanf(line, "%d %d", &v1, &v2);
    if(v1 == 0 && v2 == 0) break;
    addEdge(gph, v1, v2);
  }
  printGraph(output, gph);
  List L;
  int start = 0;
  while(fgets(line, MAX_LEN, input) != NULL) {
    int v1 = 0;
    int v2 = 0;
    start ++;
    sscanf(line, "%d %d", &v1, &v2);

    if(v1 == 0 && v2 == 0) break;
    if(start != 1) fprintf(output, "\n");
    fprintf(output, "\n");
    BFS(gph, v1);
    int dist = getDist(gph, v2);
    fprintf(output, "The distance from %d to %d is ", v1, v2);
    if(dist == -255) {
      fprintf(output, "infinity\n");
    } else {
      fprintf(output, "%d\n", dist);
    }
    L = newList();
    getPath(L, gph, v2);
    if(front(L) == -254){
      fprintf(output, "No %d-%d path exists", v1, v2);
    } else {
      fprintf(output, "A shortest %d-%d path is: ", v1, v2);
      printList(output, L);
    }


    freeList(&L);
  }
  // memory freeing
  fprintf(output, "\n");
  freeGraph(&gph);
  fclose(input);
  fclose(output);
  return(0);
}
