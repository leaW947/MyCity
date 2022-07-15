#include "headers/main.h"

#include "utils.c"
#include "gameplayService.c"
#include "assetManager.c"
#include "sceneLoader.c"

void load(SDL_Renderer *pRenderer,int pScreenWidth,int pScreenHeight){
  

    ///add images and sounds
    assetManager_addImage(pRenderer,"images/tiles/tiles.png");
    
    assetManager_addImage(pRenderer,"images/buildings/homes.png");
    assetManager_addImage(pRenderer,"images/buildings/buildings.png");
    assetManager_addImage(pRenderer,"images/buildings/buildings_$.png");

    assetManager_addImage(pRenderer,"images/icons/iconsTiles.png");
    assetManager_addImage(pRenderer,"images/icons/iconsIndex.png");
    assetManager_addImage(pRenderer,"images/icons/icons.png");

    assetManager_addImage(pRenderer,"images/icons/bubble.png");
    assetManager_addImage(pRenderer,"images/icons/dollars.png");

    assetManager_addImage(pRenderer,"images/icons/iconFire.png");
    assetManager_addImage(pRenderer,"images/tiles/fireAnim.png");

    ///BG
    assetManager_addImage(pRenderer,"images/BG/BG_Game.png");
    assetManager_addImage(pRenderer,"images/BG/BG_Menu.png");

    ///btnMenu
    assetManager_addImage(pRenderer,"images/BG/btnMenu.png");

    ///sounds
    assetManager_addSound("sounds/musics/originals/Grand-Amour.mp3","music");

    gameplayService_setSizeScreen(pScreenWidth,pScreenHeight);
    gameplayService_setRenderer(pRenderer);

    sceneLoader_load();
    sceneLoader_init("menu");
    
}

void update(float dt){
    sceneLoader_update(dt);
}

void draw(){
    sceneLoader_draw();
}

void keypressed(SDL_Scancode pKey){
    sceneLoader_keypressed(pKey);

}

void mousepressed(Uint8 pBtn,int pX, int pY){
    sceneLoader_mousepressed(pBtn,pX,pY);
}

void mousemoved(int pX, int pY){
   
    sceneLoader_mousemoved(pX,pY);

}

void mousewheel(int pY){
    
    sceneLoader_mousewheel(pY);

}

void deleteAsset(){
    
    assetManager_deleteAssets();
    graphics_deleteTexture();

}