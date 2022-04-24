#include<stdio.h>


int homer(int);

int bart(int value){
  if (value<=1) return 1;//pas de 0 => bascule infinie vers des points <0
  //cas -2 puis les cas de base prennent en compte que les 0.
  return homer(value-2)+1;
}

int homer(int value){
  if (value<=0) return 1;
  return bart(value-1)+3;//ca arrive a un appel en 0 donc 1 transmis a homer.
}
//<= des que anormal bascule valeur<=0 (=OUimportant) break<=><=>return;

int main(){
  homer(10);
}
