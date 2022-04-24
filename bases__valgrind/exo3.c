#include<stdio.h>
#include<stdlib.h>


int main(){
  int* t=malloc(sizeof(*t)*10);
  for(int i=0;i<10;++i)
    //acces lecture
    printf("%d\n",*(t+i));
  return 0;
}
