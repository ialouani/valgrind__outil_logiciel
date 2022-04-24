#include<stdio.h>
#include<stdlib.h>


int main(){
  int **n=malloc(sizeof(int*)*5);//tableau de 5 pointeurs.
  for(int i=0;i<5;++i){
    n[i]=malloc(sizeof(*n[i])*2);//matrice 2*5.
  }
  free(n);
  return 0;
}
//definitely lost car les donnees ont ete completement perdues par la libe-
//ration de l'acces n de type int**.
