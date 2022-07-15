#include "headers/mapManager.h"

#include "mapTiles.c"
#include "mapBuildings.c"
#include "fireManager.c"

void mapManager_load(){

    mapTiles_init(gameplayService_screenWidth/2+50,10);
    mapTiles_setImage(assetManager_getImage("images/tiles/tiles.png"),
                      assetManager_getImage("images/icons/iconsTiles.png"),
                      assetManager_getImage("images/icons/iconsIndex.png"),
                      assetManager_getImage("images/icons/icons.png"));

    mapBuildings_init();
    mapBuildings_setImages(assetManager_getImage("images/buildings/homes.png"),
                           assetManager_getImage("images/buildings/buildings.png"),
                           assetManager_getImage("images/buildings/buildings_$.png"),
                           assetManager_getImage("images/icons/iconsIndex.png"),
                           assetManager_getImage("images/icons/icons.png"),
                           assetManager_getImage("images/icons/bubble.png"),
                           assetManager_getImage("images/icons/dollars.png"));

    fireManager_load(assetManager_getImage("images/tiles/tiles.png"),
                     assetManager_getImage("images/icons/iconFire.png"),
                     assetManager_getImage("images/tiles/fireAnim.png"));
}

void mapManager_update(float dt){
    
    mapTiles_update(dt);
    mapBuildings_update(dt);
    fireManager_update(dt);

}

void mapManager_draw(SDL_Renderer *pRenderer){
    
    mapTiles_draw(pRenderer);
    fireManager_draw(pRenderer);
    mapBuildings_draw(pRenderer);

}

void mapManager_mousepressed(Uint8 pBtn,int pX,int pY){

    mapBuildings_mousepressed(pBtn,pX,pY);
    mapTiles_mousepressed(pBtn,pX,pY); 
    fireManager_mousepressed(pBtn,pX,pY);
   
}

void mapManager_mousemoved(int pX,int pY){
    
    mapTiles_mousemoved(pX,pY);
    mapBuildings_mousemoved(pX,pY);

}

void mapManager_keypressed(SDL_Scancode pKey){
    
    mapBuildings_keypressed(pKey);

}

void mapManager_mousewheel(int pY){
    
    mapTiles_mousewheel(pY);
    mapBuildings_mousewheel(pY);

}