#include<stdio.h>
#include<stdlib.h>

int main(){
  /*
  malloc(10);//definitely lost car depilement (void*) et adresse existante
  //mais reelement inaccessible;voila.
  */
  char* t=malloc(sizeof(*t)*3);//int[3] par exemple().///
  //de meme.
  //conclusion: sans retour ou avec retour implique ce qu'on a dit dans le
  //premier cas car sans retour ca renvoir quelque chose qui se traduit
  //par une allocation qui a la fin du programme n'existe plus
  //normalement=>same case.
  return 0;
}
