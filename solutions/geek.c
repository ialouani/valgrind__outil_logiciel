#include<stdio.h>
#include<stdlib.h>

struct Cell {
  int value;
  struct Cell *next;
};

struct Cell *newCell(int value){
  struct Cell *p=malloc(sizeof *p);//1er probleme MAJEUR+.//((()))
  if (p==NULL) exit(2);
  p->value=value;
  return p;
}

void sortInsert(struct Cell **head, struct Cell *cell){
  if (*head==NULL){
    *head=cell;
    return;
  }
  if ((*head)->value>=cell->value){
    cell->next = *head;
    *head = cell;
    return;
  }
  sortInsert(&((*head)->next),cell);
}

void power2(struct Cell *list){
  if (list==NULL) return ;
  list->value = list->value * list->value;
  power2(list->next);
}

void freeList(struct Cell *list){
  if(list->next==NULL) {
    free(list);//test sur list->next et pas de return car on doit faire un free
    //si on remonte jusqu'au bout(### de faire ce qui a ete fait).
  }
  else
    {
  freeList(list->next);//remonte jusqu'au bout par des appels recursifs:
  //list->next->..->next==NULL et liberation du dernier maillon.

  //cela a ete fait on revient successivement jusqu'A la prochaine etape
  //on a appele la fonction free sur tous les maillons a part list
  //reste a faire un free sur list suivant cette derniere etape.
  
  free(list);//ici un br (appel up apres br main puis step puis n..n)
  //puis tout avant(apres step):disp list fait le 1er free puis au deuxieme
  //affiche un double free: tcache 2 (detected in..)=>normal
  //car le premier libere l'acces au champs et l'appel recursif tente d'acceder
  //a ce champ voire de le liberer alors qu'il est indirectly lost et puis
  //en deuxieme compte(sans parlet de valgrind) un free(free(list)) genere
  //une erreur au niveau d'une nouvelle stack d'appel..///
    }}

void printList(struct Cell *list){
  if(list==NULL) printf("\n");
  else {
    printf("%d ",list->value);
    printList(list->next);//probleme de boucle infinie CLASSIQUE.
    //gdb sizeof() pour la premiere
    //ET: gdb *list apres un next (value meme) ou gdb list(adresse meme (fort+)).
  } 
}

int main(int argc, char **argv){
  struct Cell *list=NULL;//pour que le *head de type struct Cell* qui
  //represente &list de type struct Cell** transmis a sortInsert
  //permet de prendre en compte le CAS DE BASE.
  //gdb puis break main(initialisation de list pause probleme de
  //segmentation car..) puis remonter a la ligne 49 (mieux que sortInsert)
  //puis n puis p *list affiche un champ next bizarre compare avec les
  //valeurs classiques precedentes puis p *list->next
  //affiche un champ value anormal et un champ next de type d'adressage
  //totalement different=>initialisation sans NULL =>prise en compte
  //de cela=>seg fault a la fin..=>faire struct Cell* list=NULL avant de
  //passer le parametre &list a l'argument de sortInsert de type
  //struct Cell**.(rejoint l'avant derniere remarque)
  int i,j;
  for( j=0;j<5;++j){    
    for(i=0;i<5;++i)
      sortInsert(&list,newCell(random()%23));  
    printList(list);//voir derniere remarque.
    power2(list);
    printList(list);
    freeList(list);//dernier probleme:free resolu voir plus haut fonction concernee.
    //initialisation de list a NULL pour que le prochain tour utilise au niveau de sortInsert la bonne valeur.
    list=NULL;
  }
  return EXIT_SUCCESS;
}
