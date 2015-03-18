#include <grid.h>
#include <stdlib.h>
#include <stdio.h>

int NOMBREMOUVEMENTS=5;


struct sommet{
  int pere;
  int nbFils;
  int * fils;
  grid grille;
  int hauteur;
  //int direction; A voir, si bon compléter les fcts.
};

typedef struct sommet* sommet;

struct arbre{
  int racine;
  sommet tab;
  int nbSommets;
};

typedef struct arbre* arbre;

arbre creeArbre(sommet t){
  int n=4*15*NOMBREMOUVEMENTS+1;//Taille maxi de l'arbre
  arbre a=malloc(sizeof(struct arbre));
  a->tab=malloc(sizeof(struct sommet *)*n);
  for(int i=0;i<n;i++){
    a->tab[i].pere=-2;
  }
  a->racine=0;
  a->tab[0].hauteur=0;
  a->tab[0].frereDroit=-1;
  a->tab[0].pere=-1;
  a->tab[0].premierFils=1;
  a->nbSommets=1;
  return a;
}

void detruireArbre(arbre a){
  free(a->tab);
  free(a);
}

sommet creeSommet(grid g,int pere){
  sommet s=malloc(sizeof(struct sommet));
  s->pere=pere;
  s->nbFils=0;
  s->grille=g;
  s->hauteur=0;
  return s;
}

void detruireSommet(sommet s){
  free(s);
}

void ajouterEnfant(sommet feuille,arbre a){
  int i=0;
  sommet * pere;
  while(a.tab[i].pere!=-2)
    i++;
  if(feuille.nbFils==0)
    pere.fils=malloc(sizeof(int));
  pere.fils[nbFils]=i;
  pere.nbFils++;
  feuille.hauteur=pere.hauteur+1;
}
  
  

			   

void main(void){
  grid g=new_grid();
  add_tile(g);
  add_tile(g);
  sommet s=creeSommet(g);
  arbre a = creeArbre(s);
  detruireArbre(a);
  detruireSommet(s);
  delete_grid(g);
}

