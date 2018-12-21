int orderG(){
return 41;}

int sizeG(){
return 46;}

int are_adjacent(int u, int v){
 if(0<= u && 0<=v && u<orderG() && v<orderG()){
     if (u<40 && v<40){
         return (
                 (
                  ((int)(u / 10) == (int)(v / 10)) 
                  && ( ((30 + u - v)% 10 == 1) 
                      || ((30 + v - u)% 10 == 1) 
                     )

                 )
                 || 
                 ((u % 20 == 9) && (v % 20 == 9))
                 ||
                 (( u%20 == 19) && (v % 20 == 19))
                )
             ;
     }
     else {
         if (u>v){
             int x=u; u=v; v=x;}
         return (
                 (v==40 && u % 10 == 0)
                );
     }
 }
 else return 0;
}

