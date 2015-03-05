#include <grid.h>


struct sommet{
  int pere;
  int premierFils;
  int frereDroit;
  grid grille;
  int hauteur;
};

typedef struct sommet* sommet;

struct arbre{
  int racine;
  sommet *tab;
  int nbSommets;
};

typedef struct arbre* arbre;

arbre creeArbre(sommet* t, grid g){
  arbre a=malloc(syzeof(arbre));
  a.racine=0;
  a.tab=malloc(syzeof(sommet)*TAILLEARBRE);//TAILLEARBRE a voir suivant la grille de départ
  a.tab[0].grille=g;
  a.tab[0].hauteur=0;
  a.tab[0].frereDroit=NULL;
  a.tab[0].pere=NULL;
  a.tab[0].premierFils=1;
  a.nbSommets=1;
}

void detruireArbre(arbre a){
  for(int i=0;i<nbGrid;i++){
    free(a.tab[i]);
  }
  free(a.tab);
  free(a);
}


    
  
