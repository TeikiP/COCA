int orderG(){
return 34;}

int sizeG(){
return 36;}

int are_adjacent(int u, int v){
 if(0<= u && 0<=v && u<orderG() && v<orderG()){
     if (u<30 && v<30){
      return (
          ((int)(u/10)==(int)(v/10)) && ( ((30+u-v)%10==1) || ((30+v-u)%10==1) )
          );
     }
     else {
         if (u>v){
            int x=u; u=v; v=x;}
         return (
                 (u>=30 && v==33)
                 ||
                 ((u%10)==0 && (int)(u/10)==(v%10))
                );
     }
 }
 else return 0;
}

