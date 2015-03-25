#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <grid.h>
#include <grid_utilities.h>
#include <SDL2/SDL.h>

bool jouer = true;
int goFullscreen = false;
int * pGoFullscreen = &goFullscreen;
void eventHappens();
void draw();
SDL_Event event;

void eventHappens(){
    while(SDL_PollEvent(&event)){ // Fonction non bloquante, s'exe si utilisé mais sans mettre en pause le programme
        switch(event.type){
            case SDL_QUIT:
                jouer = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_q:
                        jouer = false;
                        break;
                    case SDLK_t:
                        fprintf(stdout, "test\n");
                        break;
                    // case SDLK_f:
                        // once = false;
                        // *pGoFullscreen = true;
                        // break;
                        // case SDLK_m:
                        //     SDL_Rect dest2 = {450, 150, pSprite->w, pSprite->h};
                        //     SDL_RenderCopy(pRenderer,pTexture,NULL,&dest2); // Copie du sprite grâce au SDL_Renderer
                        //     break;
                    // case SDLK_UP:
                    //     if(can_move(g, UP))
                    //       play(g,UP);
                    //     break;
                    // case SDLK_DOWN:
                    //     if(can_move(g, DOWN))
                    //       play(g,DOWN);
                    //     break;
                    // case SDLK_LEFT:
                    //     if(can_move(g, LEFT))
                    //       play(g,LEFT);
                    //     break;
                    // case SDLK_RIGHT:
                    //     if(can_move(g, RIGHT))
                    //       play(g,RIGHT);
                    //     break;
                    }
        }
    }
}

void draw(){
    SDL_Window* pWindow;
    SDL_Init(SDL_INIT_VIDEO);
    //pWindow = SDL_SetVideoMode(1920, 1080, 32, SDL_WINDOW_RESIZABLE);
    pWindow = SDL_CreateWindow("2048",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_RESIZABLE);
    // penser à vérifier les mallocs...


    if( pWindow ){
        SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle
        SDL_Surface *pSprite;
        char name_tile[15];

        grid g = new_grid();
        add_tile(g);
        add_tile(g);

        while (jouer){
            for(int i=0; i<GRID_SIDE; i++){
                for(int j=0; j<GRID_SIDE; j++){
                    //set_tile(g, 0, 0, 11);

                    // eventHappens();
                    // problème de variable locale ?


                    while(SDL_PollEvent(&event)){ // Fonction non bloquante, s'exe si utilisé mais sans mettre en pause le programme
                        switch(event.type){
                            case SDL_QUIT:
                                jouer = false;
                                break;
                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym){
                                    case SDLK_q:
                                        jouer = false;
                                        break;
                                    case SDLK_a:
                                        add_tile(g);
                                        fprintf(stdout, "ajout d'une nouvelle tuile\n");
                                        break;
                                    // case SDLK_f:
                                        // once = false;
                                        // *pGoFullscreen = true;
                                        // break;
                                        // case SDLK_m:
                                        //     SDL_Rect dest2 = {450, 150, pSprite->w, pSprite->h};
                                        //     SDL_RenderCopy(pRenderer,pTexture,NULL,&dest2); // Copie du sprite grâce au SDL_Renderer
                                        //     break;
                                    case SDLK_UP:
                                        if(can_move(g, UP))
                                          play(g,UP);
                                        break;
                                    case SDLK_DOWN:
                                        if(can_move(g, DOWN))
                                          play(g,DOWN);
                                        break;
                                    case SDLK_LEFT:
                                        if(can_move(g, LEFT))
                                          play(g,LEFT);
                                        break;
                                    case SDLK_RIGHT:
                                        if(can_move(g, RIGHT))
                                          play(g,RIGHT);
                                        break;
                                    }
                        }
                    }

                    sprintf(name_tile, "../images/%d.bmp", (int)pow(2,get_tile(g,i,j)));
                    pSprite = SDL_LoadBMP(name_tile);
                    // cette ligne se débrouille pour aller chercher un fichier image après avoir modfié une
                    // string, par ex pour get_tile = 0, ça fait 2^0 = ../images/1.bmp
                    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);
                    // SDL_Rect dest = { i - pSprite->w/2, j - pSprite->h/2, pSprite->w, pSprite->h};
                    SDL_Rect dest = { 200 + i*100, 200 + j*100, pSprite->w, pSprite->h};
                    SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);
                    SDL_RenderPresent(pRenderer);
                    SDL_DestroyTexture(pTexture);
                }
            }
            SDL_FreeSurface(pSprite);
        }
    }

}

int main(int argc, char** argv){

    if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    // partie test pour le highscore avec l'input et l'output dans un fichier

    // int tableau[5] = {0, 1, 0, 1, 1}, i = 0;
    // for (i = 0 ; i < 5 ; i++){
    //     if (tableau[i]==0)
    //         printf("nice :D\n");
    //     else if(tableau[i]==1)
    //         printf("Num 1 là !\n");
    //     //printf("%d\n", tableau[i]);
    // }

    draw();
    return EXIT_SUCCESS ;   
}