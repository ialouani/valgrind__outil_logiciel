#include<stdio.h>
#include<stdlib.h>


int main(){
  int **n=malloc(sizeof(int*)*5);//tableau de 5 pointeurs.
  for(int i=0;i<5;++i){
    n[i]=malloc(sizeof(*n[i])*2);//matrice 2*5.
  }
  //free(n);
  return 0;
}

//definitely lost pour 40=8*5 bytes(octets) dans un seul block
//et vu que l'acces des prochains tableaux(contenane(s))
//est perdue car le n est perdue => indirectly lost.
//ce qui veut dire que les donnees ont ete indirectement perdues
//par un defaut de liberation de l'origine impliquant sa perte
//a la fin du programme et la perte du tas successif en terme
//de contenant de n(matrice) etant indirectement perdues.
//20 bytes in 5 blocks car chaque block contient 2*4=8 *5=40 en 5 lignes
//=>5 blocks.
//6 allocs 1 free pour le premier et de meme sauf 0 free pour le deuxieme
//(current file).
