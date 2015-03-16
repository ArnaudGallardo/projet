#include "grid.h"
#include "grid_utilities.h"


/**
 * \brief Dessine de maniere rudimentaire la grille dans l'affichage par default
 */
void draw_grid(grid g){
  printf("-------------\n");
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      printf("%i",get_tile(g,x,y));
    }
    printf("\n");
  }
  printf("-------------\n");
}


/**
 * \brief Verifie l'egalite de deux grilles
 * \return true if equals, false if not equals
 */
bool equals(grid g1, grid g2)
{
  bool res = true;
  for(int i=0;i<GRID_SIDE;i++)
    {
      for(int j=0;j<GRID_SIDE;j++)
	{
	  if(get_tile(g1,i,j)!=get_tile(g2,i,j))
	    res = false;
	}
    }
  if(grid_score(g1)!=grid_score(g2))
    res=false;
  return res;
}


/**
 * \brief En partant d'un tableau 1D representant une ligne verticale ou horizontale d'une grille, modifie
            ce tableauen en empilant les tuiles identiques (l'empilement se fait de la fin du tableau vers le debut)
 * \return Le score resultat du mouvement
 */
int compute_array(int array[], int *size){
  int score=0;
  for(int i=1;i<*size;i++){
    if(array[i-1]==array[i]) {
      array[i-1]+=1;
      score+=pow(2,array[i-1]);
      for(int j=i+1;j<*size;j++){
	array[j-1]=array[j];
      }
      *size-=1;
    }
  }
  return score;
}

/**
 * \brief Transforme une grille en une ligne (tableau 1D de taille size) selon les parametres de position donnes et sans prendre en compte les zeros
 * \param g la grille a utiliser
 * \param array le tableau 1D
 * \param size la taille du tableau
 * \param x la position de la ligne dans le tableau
 * \param invert permet de lire la grille dans un sens ou dans l'autre (lecture de base : de haut en bas, permet de passer de bas en haut)
 * \param horizontal permet de lire la grille verticalement ou horizontalement
 */
void grid_to_array(grid g, int array[], int *size, int x, bool invert, bool horizontal)
{
  *size=0;
  int tmp = x;
  for(int y=0;y<GRID_SIDE;y++){
    if(horizontal)
      {
	x = y;
	y = tmp;
      }
    if(get_tile(g,x,y)!=0){
      array[*size]=get_tile(g,x,y);
      *size+=1;
    }
    if(horizontal)
      y=x;
  }
  if(invert)
    invert_array(array, size);
}

/**
 * \brief Inverse un tableau 1D de taille size
 * \param array le tableau a inverser
 * \param size la taille du tableau
 */
void invert_array(int array[], int *size)
{
  int tmp;
  for(int i=0;i<*size/2;i++)
    {
      tmp = array[i];
      array[i]=array[*size-i-1];
      array[*size-i-1]=tmp;
    }
}

/**
 * \brief Effectue l'action inverse de grid_to_array (voir grid_to_array), en rajoutant des zeros
 * \param g la grille a utiliser
 * \param array le tableau 1D
 * \param size la taille du tableau
 * \param x la position de la ligne dans le tableau
 * \param invert permet de lire la grille dans un sens ou dans l'autre (lecture de base : de haut en bas, permet de passer de bas en haut)
 * \param horizontal permet de lire la grille verticalement ou horizontalement
 */
void array_to_grid(grid g, int array[], int *size, int x, bool invert, bool horizontal)
{
  int tmp = x;
  int tp;
  for(int y=0;y<GRID_SIDE;y++){
    tp = y;
    if(horizontal)
      {
	x = y;
	y = tmp;
      }
    if(invert)
      {
	if(tp<GRID_SIDE-(*size))
	  set_tile(g,x,y,0);
	else
	  set_tile(g,x,y,array[GRID_SIDE-tp-1]);
      }
    else
      {
	if(tp<*size)
	  set_tile(g,x,y,array[tp]);
	else
	  set_tile(g,x,y,0);
      }
    if(horizontal)
      y=x;
  }
}
