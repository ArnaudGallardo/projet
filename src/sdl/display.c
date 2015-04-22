#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <grid.h>
#include <grid_utilities.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

bool continueToPlay = true;
void eventHappens(grid g);
void draw();
SDL_Event event;

void eventHappens(grid g){
    SDL_WaitEvent(&event);
    switch(event.type){
        case SDL_QUIT: // when the window is closed by the cross
            continueToPlay = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){ // when a key is pressed
                case SDLK_q:
                    continueToPlay = false;
                    break;
                case SDLK_r:
                    delete_grid(g);
                    g = new_grid();
                    add_tile(g);
                    add_tile(g);
                    break;
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
                break;
                default:
                    break;
            }
        default:
            break;
    }
}

void draw(){
    SDL_Init(SDL_INIT_VIDEO); // initiate the SDL
    SDL_Surface *screen = NULL, *textTitle = NULL, *textGoal = NULL, *imageTile = NULL, *background = NULL, *textScore = NULL, *score = NULL, *resetBackground = NULL, *textHowTo = NULL, *textGameOver = NULL;
    SDL_Rect positionTile, positionTitle, positionGoal, positionBackScore,positionTextScore, positionScore, positionHowTo, positionGameOver;
    SDL_Color colorWhite = {255, 255, 255}, colorTitle = {119, 110, 101}, colorTextScore = {216, 205, 193};
    TTF_Font *font = NULL;
    char tileName[15], charScore[20];

    screen = SDL_SetVideoMode(600, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE); // name (resizable) of the screen
    SDL_WM_SetCaption("2048 - The Game", NULL);
    TTF_Init(); // initiate the SDL_ttf
    font = TTF_OpenFont("../font/font.ttf", 60);

    grid g = new_grid();
    add_tile(g);
    add_tile(g);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 250, 248, 239)); // background of the GUI
    positionTitle.x = 100;
    positionTitle.y = 90;
    textTitle = TTF_RenderText_Blended(font, "2048", colorTitle);
    SDL_BlitSurface(textTitle, NULL, screen, &positionTitle);

    background = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 65, 32, 0, 0, 0, 0);
    resetBackground = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 40, 32, 0, 0, 0, 0); // updates the score

    positionBackScore.x = 350;
    positionBackScore.y = 90;
    SDL_FillRect(background, NULL, SDL_MapRGB(screen->format, 187, 173, 160)); 
    SDL_BlitSurface(background, NULL, screen, &positionBackScore);
    
    font = TTF_OpenFont("../font/font.ttf", 15); // the font and it's size
    positionGoal.x = 100;
    positionGoal.y = 160;
    textGoal = TTF_RenderText_Blended(font, "Try to reach the highest tile you can !", colorTitle);
    SDL_BlitSurface(textGoal, NULL, screen, &positionGoal);

    
    font = TTF_OpenFont("../font/font.ttf", 15);
    positionTextScore.x = 400;
    positionTextScore.y = 95;
    textScore = TTF_RenderText_Blended(font, "Score", colorTextScore);
    SDL_BlitSurface(textScore, NULL, screen, &positionTextScore);

    positionHowTo.x = 100;
    positionHowTo.y = 610;
    textHowTo = TTF_RenderText_Blended(font, "Shortcuts: Q [Quit], R [Restart] and directionnal arrows.", colorTitle);
    SDL_BlitSurface(textHowTo, NULL, screen, &positionHowTo);
    font = TTF_OpenFont("../font/font.ttf", 30);

    while(continueToPlay){
        for(int i=0; i<GRID_SIDE; i++){
            for(int j=0; j<GRID_SIDE; j++){
                sprintf(tileName, "../images/%d.bmp", (int)pow(2,get_tile(g,i,j)));
                imageTile = SDL_LoadBMP(tileName);
                positionTile.x = 100 + 100* i; // base positionning
                positionTile.y = 200 + 100* j;
                SDL_BlitSurface(imageTile, NULL, screen, &positionTile);
                SDL_Flip(screen);

                if(get_tile(g, i, j) == 11 || game_over(g)){ // maximal tile which can be reached or unable to move
                    positionGameOver.x = 100;
                    positionGameOver.y = 650;
                    textGameOver = TTF_RenderText_Blended(font, "Game Over !", colorTitle);
                    SDL_BlitSurface(textGameOver, NULL, screen, &positionGameOver);
                    SDL_Flip(screen);
                    SDL_Delay(300);
                    continueToPlay = false;
                }
            }
        }

        positionScore.x = 380;
        positionScore.y = 110;
        SDL_FillRect(resetBackground, NULL, SDL_MapRGB(screen->format, 187, 173, 160));
        SDL_BlitSurface(resetBackground, NULL, screen, &positionScore);

        sprintf(charScore, "%lu", grid_score(g));
        score = TTF_RenderText_Blended(font, charScore, colorWhite);
        SDL_BlitSurface(score, NULL, screen, &positionScore);
        SDL_Flip(screen);
        eventHappens(g);
    }

    TTF_CloseFont(font);
    TTF_Quit(); // leaving the SDL_ttf
    SDL_FreeSurface(textTitle); SDL_FreeSurface(textGoal); SDL_FreeSurface(imageTile); SDL_FreeSurface(background); SDL_FreeSurface(textScore); SDL_FreeSurface(score); SDL_FreeSurface(resetBackground); SDL_FreeSurface(textHowTo); SDL_FreeSurface(textGameOver);
    SDL_Quit(); // free of screen and free of all the others above
}

int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
        fprintf(stdout,"Fail starting the SDL... (%s)\n",SDL_GetError());
        return -1;
    }
    draw();
    return EXIT_SUCCESS ;   
}