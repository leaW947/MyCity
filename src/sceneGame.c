#include "headers/sceneGame.h"

#include "GUIManager.c"
#include "mapManager.c"

static SDL_Texture *imgMoney;
static TTF_Font *fontMoney;
static SDL_Texture *textMoney;

static int oldMoney=0;
char charMoney[50];

static SDL_Texture *imgBGGame;

Mix_Music *musicGame;

void sceneGame_load(){

    musicGame=assetManager_getMusic("sounds/musics/originals/Grand-Amour.mp3");
    Mix_PlayMusic(musicGame,-1);

    gameplayService_money=500000;
    oldMoney=gameplayService_money;

    imgMoney=assetManager_getImage("images/icons/dollars.png");
    fontMoney=graphics_newFont("./font/Baby Doll.ttf",30);

    textMoney=graphics_newText(gameplayService_renderer,fontMoney,itoa(gameplayService_money,charMoney,10),NULL);

    imgBGGame=assetManager_getImage("images/BG/BG_Game.png");

    mapManager_load();

}


void sceneGame_update(float dt){

    mapManager_update(dt);

    if(oldMoney!=gameplayService_money){

        fontMoney=graphics_newFont("./font/Baby Doll.ttf",30);
        textMoney=graphics_newText(gameplayService_renderer,fontMoney,itoa(gameplayService_money,charMoney,10),NULL);

        oldMoney=gameplayService_money;

    }
}


void sceneGame_draw(){

    SDL_Rect rectSrBG={0,0,gameplayService_screenWidth,gameplayService_screenHeight};
    SDL_Rect rectDsBG={0,0,gameplayService_screenWidth,gameplayService_screenHeight};

    SDL_RenderCopy(gameplayService_renderer,imgBGGame,NULL,&rectDsBG);

    mapManager_draw(gameplayService_renderer);
    
    ///img dollars
    graphics_draw(gameplayService_renderer,imgMoney,gameplayService_screenWidth-150,5);

    graphics_drawText(gameplayService_renderer,textMoney,gameplayService_screenWidth-110,5);

}


void sceneGame_keypressed(SDL_Scancode pKey){

    mapManager_keypressed(pKey);

}

void sceneGame_mousepressed(Uint8 pBtn,int pX,int pY){

    mapManager_mousepressed(pBtn,pX,pY);

}

void sceneGame_mousemoved(int pX,int pY){
    mapManager_mousemoved(pX,pY);
}

void sceneGame_mousewheel(int pY){

    mapManager_mousewheel(pY);

}


