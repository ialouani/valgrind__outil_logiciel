#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 13 // prime number

struct Cell {
  void *donnee;
  struct Cell *next,*prev;
};

struct hash_Table{
  int (*cmp)(void *,void *);
  int (*hash)(void *);
  struct Cell **entry;
  int size;
};

struct Cell *hash_newcell(void *donnee){
  struct Cell *c=malloc(sizeof(*c));
  c->donnee=donnee;
  c->next=c->prev=NULL;
  return c;
}

struct hash_Table *hash_init(int (*cmp)(void *,void *), int (*hash)(void *)){
  struct hash_Table *hasht;
  int i;
  assert(cmp!=NULL);
  assert(hash!=NULL); 
  hasht = malloc(sizeof(*hasht));
  if (hasht==NULL) return NULL;
  hasht->cmp=cmp;
  hasht->hash=hash;
  hasht->entry=malloc(sizeof(*(hasht->entry))*HASH_SIZE);
  if (hasht->entry==NULL){
    free(hasht);
    return NULL;
  }
  hasht->size=HASH_SIZE;
  for(i=0;i<hasht->size;++i) hasht->entry[i]=NULL;
  return hasht;
}

int HashAdd(struct hash_Table *hash,void *donnee){
  int value;
  int c;
  struct Cell *cell=hash_newcell(donnee);//allocation de plus*
  //* pour gestion: voir plus bas.
  assert(hash!=NULL);
  value=hash->hash(donnee);  
  fprintf(stderr,"DEBUG: hash value is %d \n",value);
  if (hash->entry[value%hash->size]==NULL){
    hash->entry[value%hash->size]=cell;
  } else {
    struct Cell *q=NULL,*p=hash->entry[value%hash->size];
    while((p!=NULL) && ((c=hash->cmp(donnee,p->donnee))>0)){
      q=p;
      p=p->next;    
    }
    if (c==0){
      free(cell);//deja existant voir commentair plus bas.
	return 1; // element is already in the table
       }
    if (q==NULL){
      p->prev=cell; cell->next=p;
      hash->entry[value%hash->size]=cell;
    }else{
      q->next = cell; cell->prev=q;
    } 
  }
  return 0;
}

int hashCherche(struct hash_Table *hash,void *donnee){
  int r=0,value;
  assert(hash!=NULL);
  value=hash->hash(donnee);  
  struct Cell *p=hash->entry[value%hash->size];
  while((p!=NULL) && (r=hash->cmp(donnee,p->donnee)<0))
    p=p->next;
  if (r==0) return 0;
  if (p==NULL) return 1;
  return 1;
}

void hash_free(struct hash_Table *hash, void (*release)(void *)){
  int i;
  assert(hash!=NULL);
  for(i=0;i<hash->size;++i){
    struct Cell *p=hash->entry[i];
    if (p==NULL) continue;
    while(p->next!=NULL){
      p=p->next;
      if (release!=NULL)
	release(p->prev->donnee);
    }
    free(p);//ici pas avant avant car dernier maillon detecte par list->next==NULL.
  }
  free(hash->entry);
  free(hash);    
}


#include <string.h>
#include <stdio.h>

int str_hash(unsigned char *str)
{
  int hash = 5381;
  int c;
  
  while ((c = *str++)!='\0')
    hash = ((hash << 5) + hash) + c; 
  
  return hash;
}


int main(){
  struct hash_Table *hash=hash_init((void *)strcmp,(void *)str_hash);
  printf("add toto %d \n",HashAdd(hash,"toto"));
  printf("add titi %d \n",HashAdd(hash,"titi"));
  printf("ajout titi %d \n",HashAdd(hash,"titi"));
  printf("toto => %d\n",hashCherche(hash,"toto"));
  printf("titi => %d\n",hashCherche(hash,"titi"));
  printf("tbtb => %d\n",hashCherche(hash,"tbtb"));
  hash_free(hash,NULL);
  return EXIT_SUCCESS;
}
