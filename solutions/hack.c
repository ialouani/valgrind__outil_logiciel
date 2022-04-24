#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void randstack(int i){
  int j=random();
  if (i>0)
    randstack(i-1);
}

struct Cell {
  int value;
  struct Cell * next, * prev;
};

struct Cell *newCell(int value){
  struct Cell *p=malloc(sizeof *p);
  if (p==NULL) exit(2);
  p->value = value;
  return p;
}

struct Cell * append(struct Cell *list, struct Cell *newCell){
  struct Cell *p;
  if (list==NULL) return newCell;
  p=list;
  while(p->next != NULL) p=p->next;
  p->next = newCell;
  newCell -> prev = p;
  return list;
}

struct Cell *removeValue(struct Cell *list , int value){
  struct Cell *tmp;
  if (list==NULL) return NULL;
  if (list->value==value) {
    tmp=list->next;
    free(list);
    return removeValue(tmp,value);
  }
  list->next  = removeValue(list->next,value);
  return list;
}

struct Cell *reverseList(struct Cell *list){
  struct Cell *tmp;
  if (list==NULL) return NULL;  
  tmp = list->next;//1..99
  list->next = list->prev;//list devient en *: ?? -> NULL
  list->prev=tmp;//=> 1 .. 99 <- ?? -> NULL.
  if (tmp==NULL)//si list->prev==NULL donc retour de list(<=>on a rien fait..)///
    return list;
  else{
    //tmp se decale et *tmp 1 centre (preuve) et *list |0|  d'apres le premier
    //tour degdb et l'observation du cas debase c'est list qui va etre retourne
    //au bout de 99 decalage de tmp (99 appels recursifs) donc list
    //doit se linker avec tmp car 1er tour=> 01 en 10 si list=tmp->prev.
    //ou L'INVERSE si on doit se confier a tmp uniquement(argument de re(appel)).
    tmp->prev=list;//on inverse au 1er tour par transfo: 01 en 10
    //via la cmd:: tmp->prev=list car *list en gdb affiche 0 donc *tmp devient
    //0|1|..99 puis on refait la meme procedure suivant tmp car tmp->prev en affect. pas list.
    return reverseList(tmp);
  }}

void print(struct Cell *l){
  if (l==NULL) {
    printf("\n"); 
    return;
  }
  printf("%d ",l->value);
  print(l->next);
}

void freeList(struct Cell *l){
  struct Cell *tmp;
  if (l==NULL) return;
  tmp=l->next;
  free(l);
  freeList(tmp);
}

int main(){
  struct Cell *list = NULL;
  int i;
  randstack(100);
  for(i=0;i<100;++i)
    list = append(list,newCell(i));
  print(list);
  for(i=10;i<50;i+=2)
    list = removeValue(list,i);
  print(list);
  list = reverseList(list);
  print(list);
  freeList(list);
  return EXIT_SUCCESS;
}
  
