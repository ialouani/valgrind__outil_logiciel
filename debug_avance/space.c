#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>//toupper prise en compte meme si -std=c99

void randstack(int i){
  int j=rand();//-std=c99 implique pas random.(rand) gcc -g seulement
  //si random(naturel;deja rencontre..////)
  if (i>0)
    randstack(i-1);
}

char *getStr(int size){
  static char memBuffer[4096];
  static int id=0;
  char *tmp=memBuffer+id;
  id+=size+1;//static prochain using impliquerait demarrage tout a la fin
  //=>negliger le zero terminal=>augmenter de 1.(*)
  return tmp;
}


char *toUpper(char *str){
  int i;
  char *buffer=getStr(strlen(str));
  for(i=0;i<strlen(str);++i){
    buffer[i]=toupper(str[i]);
  }
  buffer[i]='\0';//(*)=>repercussions: remplir ce champ par un appel
  //sentinel qui est \0.
  return buffer;  
}

int main(){
  char *a,*b;
  randstack(100);
  a=toUpper("hello");
  b=toUpper("world!");
  printf("%s %s \n",a,b);
  
  return EXIT_SUCCESS;
}
