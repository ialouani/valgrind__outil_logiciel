#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int strcmp_rec(char *s,char *t){
  if ((s[0]=='\0') && (t[0]=='\0'))
    return 0;
  if (s[0]<t[0]) return -1;
  if (s[0]>t[0]) return 1;
  else {
    //il se peut que les deux chaines ont le 2ieme caractere meme
    //ca va renvoyer 0=>equal ce qui est pas forcement le cas.
    return strcmp_rec(s+1,t+1);
    //en cas de non return 1 exemple: hab et hba ca va retourner 1
    //alors que hab<hba donc doit retourner -1 normalement .
    //=>fixer via remonter+cas de base INCLUS.
  }
}

int main(int argc, char **argv){
  char s[]="hellob";//s est lexico-.. >= que t => strcmp renvoie nbr>0.()
  char t[]="helloa";//renvoie 1 oui mais dedans equal=>probleme.
  printf("%d*******\n",strcmp("hab","hba"));//-1 car hab<hba.
  printf("%d\n",strcmp(s,t));
  switch(strcmp_rec(s,t)){
    case 0:
      puts("equal");
      break;
    case 1:
      puts("greater");
      break;
    case 2:
      puts("smaller");
      break;
    }
  return EXIT_SUCCESS;
   
}
