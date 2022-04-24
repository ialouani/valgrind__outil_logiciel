#include <stdio.h>
#include <stdlib.h>

struct Node {
  struct Node *left;
  struct Node *right;
  int value;
};

struct Node *new_node(int v){
  struct Node *n=malloc(sizeof(*n));
  n->left=NULL;
  n->right=NULL;
  n->value=v;
  return n;
}

void print_tree_rec(struct Node *n,int level){
  int i;
  if (n==NULL) return;
  for(i=0;i<level;++i)
    printf(" ");
  printf("%d\n",n->value);
  print_tree_rec(n->left,level+1);
  printf("******\n");
  //rq:(*)!!!!!les **** affichent les retours de NULL donc remontage de la pile => inversion left/right
  //ou bien remonter jusqu'au grand-..-grand pere pour en deduire les fils de l'autre cote.
   print_tree_rec(n->right,level+1);
}

void print_tree(struct Node *n){
  print_tree_rec(n,0);
}

void add(struct Node *a, struct Node *b){
  if (b->value<a->value){
    if (a->left==NULL) a->left=b;
    else add(a->left,b);
  } else {
  //c'est facile, si a->value n'est pas grande alors a->right doit se voir affecter b
  //=>si a->right==NULL elle va recevoir b sinon on va ajouter dans a->right (###remonter(*))
  //l'element b.
    if (a->right==NULL) a->right=b;
    else add(a->right,b);    
    //procedure gdb: br 'ligne$-----<' puis r y puis step puis n n puis cond numero_breakpoint
    //(a=oxo) puis c puis p a puis p b p *a(impossible a=0X0) 
    //=>on essaie d'ajouter suivant un test de cas de base impossible =>
    //inspecter les cas de base qui impliquent les sous cas de base!
    //en particulier a->left==NULL pour le deuxieme.
    //ce qui resoud le bug.
  }
}

struct Node *build_tree(int *values,int s){
  int i;
  if (s<=0) return NULL;
  struct Node *root=new_node(values[0]);
  for(i=1;i<s;++i){
    add(root,new_node(values[i]));
  }
  return root;//pour gdb (2 up ###top---=>oxo pour l'origine(on sait de quoi on parle)).
}

void free_tree(struct Node *n){
  if (n==NULL) return;
  free_tree(n->left);
  free(n);
}


int main(){
  int t[8]={5,4,2,10,11,6,1,8};
  struct Node * n=build_tree(t,8);
  print_tree(n);
  free_tree(n);
}
