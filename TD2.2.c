int orderG(){
    return 441;
}

int sizeG(){
    return  840;
}


int are_adjacent(int u, int v){
    if(0<=u && 0<=v && u<orderG() && v<orderG())
        return(
                (
                 (
                  ((u-v)%21==1) || ((v-u)%21== 1)
                 )
                 &&
                 (v/21)==(u/21)
                )
                ||
                (
                 (
                  (u/21-v/21)==1 || (v/21-u/21 ) == 1
                 )
                 &&
                 (v%21)==(u%21)
                 )
              );
    return 0;
}





