#include "Test.h"
#include <iostream>
#include "Edge.h"
#include <cstring>

using namespace std;

int** initGraph(int size)
{
    int **answer = new int* [size];
    for(int i=0;i<size;i++)
    {
        answer[i]=new int[size];
        for(int j=0;j<size;j++)
        {
            answer[i][j]=-1;
        }
    }
    return answer;
}

bool checkPath(int** new_graph,int size, int* marked, int from, int to){
  marked[to] = 1;
  bool cycleFound = false;
  for(int i =0; i < size; i++){
    if(from != i && to != i ){
      if(new_graph[to][i] != -1){
        if(marked[i] == 1 ){
          return true;
        }else{
          marked[i] = 1;
          cycleFound = checkPath(new_graph,size, marked, to, i);
          if(cycleFound)
            return cycleFound;
        }
      }
    }
  }
  return cycleFound;
}
bool checkCyclesOn(int** new_graph, int size){
  int marked[size];
  memset(marked, 0, sizeof(int)*size);
  return checkPath(new_graph, size, marked, 0,0);
}
void deleteEdge(int** graph, Edge* edge){
  graph[edge->source][edge->destination] = -1;
  graph[edge->destination][edge->source] = -1;
}

void addEdge(int** graph, Edge* edge){
  graph[edge->source][edge->destination] = edge->weight;
  graph[edge->destination][edge->source] = edge->weight;
}
int** getKruskalMST(int** graph, int size, vector<Edge*> edges)
{
    int** new_graph = initGraph(size);
    for(int i = 0; i < edges.size(); i++){
      addEdge(new_graph, edges[i]);
      if(checkCyclesOn(new_graph, size)){
        deleteEdge(new_graph, edges[i]);
      }
    }
    return new_graph;
}

int main ()
{
    test();
    return 0;
}
