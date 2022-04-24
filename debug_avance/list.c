#include <stdlib.h>
#include <stdio.h>

struct list {
  int value;
  struct list *next,*prev;
};



struct list *list_new(int value){
  struct list *p=malloc(sizeof(*p));
  if (p==NULL)
    return NULL;
  p->prev=p->next=NULL;
  p->value=value;
  return p;
}

// 0. value added
// 1. memory error
int list_add_front(struct list **l, int value){
  struct list *p;
  p=list_new(value);
  if (p==NULL) return 1;
  if (*l==NULL){
    *l=p;
    return 0;
  }
  p->next=*l;
  (*l)->prev=p;
  *l=p;
  return 0;  
}

void list_print(struct list *l){  
  
  while(l->next!=NULL){
    printf("%d ",l->value);
    l=l->next;}
  printf("%d\n",l->value);
  return;
}

void list_free(struct list **l){
  if (*l==NULL) return;
  list_free(&((*l)->next));
  free(*l);
  *l=NULL;
}

int main(){
  struct list *l=NULL;
  list_add_front(&l,0);
  list_add_front(&l,4);
  list_add_front(&l,8);
  list_print(l);
  list_free(&l);
  return 1;
}
