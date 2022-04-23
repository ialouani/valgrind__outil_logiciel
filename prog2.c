#include <math.h>
#include<stdio.h>//(*)
//#include<stdlib.h>
//#include<stddef.h>

void f(double d);

int main(int argc, char *argv[]) {
  double a = 4.0;
  f(a);
  return 0;
}

void f(double d) {
  double e = sqrt(d);

  printf("sqrt(%f) = %f\n", d, e);
}

//stdio.h essentiel pour appeler la printf de la libc
//=>lors de l'édition de liens(optimisations de gcc)
//nm apres prog2.o(gcc -c prog2.c)=>U printf
//prise en compte pour la 2=>la 3 qui pose probleme.(meme si on inclut stdio.h)
//### l'etape2 (etape 1 aussi ..gcc -S...)
//resume etape 2 pour stdio(compilation): printf provide declaration missing.
///=>de meme pour f non au-dessus du main (etape de compilation)
//car a la generation d'objets il se trouve pas deja avec une pre-declaration
//de f donc warning -Werror le declare comme une erreur contrairement a(*)
//selon les versions.
//la derniere concerne: l'edition de liens: la declarations de math.h
//passe par -lm pour ramener les implementations des prototypes a savoir sqrt.
//***********************
//lors de l'appel de printf -g puis gdb a.out puis br 17() puis r puis y(r deja
//si) puis p &e/&d avec un autre processus pareil mais break main puis n
//jusqu'a double a=4.0 puis n (prise en compte sur la pile de a) puis p &a.
//rq: a est sur la pile l'entree ; sur f ; change quasiment rien en terme de &a.
//td2 --listing.///
//un simple printf 1 puis 2 fois sur f confirmera le dire.
