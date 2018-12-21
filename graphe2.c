#include "all.h"

int graph[6][6] = {
  // 0  1  2  3  4  5 
    {0, 1, 1, 0, 0, 0}, //0
    {1, 0, 0, 0, 0, 0}, //1
    {1, 0, 0, 1, 0, 0}, //2
    {0, 0, 1, 0, 0, 1}, //3
    {0, 0, 0, 0, 0, 1}, //4
    {0, 0, 0, 1, 1, 0}, //5
};

int orderG(){
return 6;
}

int sizeG(){
return 5;
}

int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}

