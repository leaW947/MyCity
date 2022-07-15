#include "headers/sceneMenu.h"


static SDL_Texture *imgBG_Menu;
static SDL_Texture *imgBtnMenu;

static int wBtn;
static int hBtn;

static int xBtn;
static int yBtn;


static bool bIsHover; 
static SDL_Rect rectCollideBtn;

void sceneMenu_load(){

    bIsHover=false;
    
    imgBG_Menu=assetManager_getImage("images/BG/BG_Menu.png");
    imgBtnMenu=assetManager_getImage("images/BG/btnMenu.png");

    wBtn=300;
    hBtn=150;

    xBtn=(gameplayService_screenWidth/2)-(wBtn/2);
    yBtn=gameplayService_screenHeight-(hBtn*1.5);


}

void sceneMenu_update(float dt){

}

void sceneMenu_draw(){

    SDL_Rect rectDsBG={0,0,gameplayService_screenWidth,gameplayService_screenHeight};
    SDL_RenderCopy(gameplayService_renderer,imgBG_Menu,NULL,&rectDsBG);

    SDL_Rect rectSrBtn;

    if(!bIsHover){

        rectSrBtn.x=0;
        rectSrBtn.y=0;
        rectSrBtn.w=wBtn;
        rectSrBtn.h=hBtn;

    }else{

        rectSrBtn.x=1*wBtn;
        rectSrBtn.y=0;
        rectSrBtn.w=wBtn;
        rectSrBtn.h=hBtn;

    }

    SDL_Rect rectDsBtn={xBtn,yBtn,wBtn,hBtn};

    SDL_RenderCopy(gameplayService_renderer,imgBtnMenu,&rectSrBtn,&rectDsBtn);
}

void sceneMenu_keypressed(SDL_Scancode pKey){

}

void sceneMenu_mousepressed(Uint8 pBtn, int pX,int pY){

    bool bCollideBtn=utils_checkCollision(pX,pY,1,1,xBtn,yBtn,wBtn,hBtn);

    if(bIsHover){
        sceneLoader_init("gameplay");
    }

}

void sceneMenu_mousemoved(int pX,int pY){

    bool bCollideBtn=utils_checkCollision(pX,pY,1,1,xBtn,yBtn,wBtn,hBtn);

    if(bCollideBtn){
        bIsHover=true;
    }else{
        bIsHover=false;
    }

}

void sceneMenu_mousewheel(int pY){

}