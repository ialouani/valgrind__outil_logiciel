#include<stdio.h>
#include<stdlib.h>


int main(){
  int* t=malloc(sizeof(*t)*10);
  for(int i=0;i<11;++i)
    //acces ecriture
    t[i]=i;
  printf("%d\n",t[10]);
  return 0;
}
