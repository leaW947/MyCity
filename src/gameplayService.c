#include "headers/gameplayService.h"

int gameplayService_screenWidth;
int gameplayService_screenHeight;

int gameplayService_money=0;

SDL_Renderer *gameplayService_renderer;

void gameplayService_setSizeScreen(int pScreenWidth,int pScreenHeight){

    gameplayService_screenWidth=pScreenWidth;
    gameplayService_screenHeight=pScreenHeight;
    
}

void gameplayService_setRenderer(SDL_Renderer *pRenderer){
    
    gameplayService_renderer=pRenderer;

}

