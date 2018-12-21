#include "all.h"

int graph[4][4] = {
  // 0  1  2  3 
    {0, 1, 1, 0}, //0
    {1, 0, 0, 1}, //1
    {1, 0, 0, 0}, //2
    {0, 1, 0, 0}, //3
};

int orderG(){
return 4;
}

int sizeG(){
return 3;
}

int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}

