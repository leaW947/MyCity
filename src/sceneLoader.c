
#include "headers/sceneLoader.h"

#include "sceneMenu.c"
#include "sceneGame.c"

static char gameState[255];

void sceneLoader_load(){

    ///play sound: Mix_PlayChannel(canal(-1),Chunk,0)
    ///play music: Mix_PlayMusic(music,loop)

}

void sceneLoader_init(char pGameState[]){
    
    strcpy(gameState,pGameState);

    if(strcmp(gameState,"menu")==0){
        
        sceneMenu_load();

    }else if(strcmp(gameState,"gameplay")==0){
        
        sceneGame_load();

    }else if(strcmp(gameState,"gameover")==0){

    }

}

void sceneLoader_update(float dt){

    if(strcmp(gameState,"menu")==0){

        sceneMenu_update(dt);

    }else if(strcmp(gameState,"gameplay")==0){

        sceneGame_update(dt);

    }else if(strcmp(gameState,"gameover")==0){

    }

}

void sceneLoader_draw(){
    
    if(strcmp(gameState,"menu")==0){

        sceneMenu_draw();

    }else if(strcmp(gameState,"gameplay")==0){
        
        sceneGame_draw();

    }else if(strcmp(gameState,"gameover")==0){

    }

}

void sceneLoader_keypressed(SDL_Scancode pKey){

    if(strcmp(gameState,"menu")==0){

        sceneMenu_keypressed(pKey);

    }else if(strcmp(gameState,"gameplay")==0){
        
        sceneGame_keypressed(pKey);

    }else if(strcmp(gameState,"gameover")==0){

    }

}

void sceneLoader_mousepressed(Uint8 pBtn,int pX, int pY){

    if(strcmp(gameState,"menu")==0){

        sceneMenu_mousepressed(pBtn,pX,pY);

    }else if(strcmp(gameState,"gameplay")==0){
       
        sceneGame_mousepressed(pBtn,pX,pY);

    }else if(strcmp(gameState,"gameover")==0){

    }

}

void sceneLoader_mousemoved(int pX, int pY){

    if(strcmp(gameState,"menu")==0){

        sceneMenu_mousemoved(pX,pY);

    }else if(strcmp(gameState,"gameplay")==0){
        
        sceneGame_mousemoved(pX,pY);

    }else if(strcmp(gameState,"gameover")==0){

    }

}

void sceneLoader_mousewheel(int pY){

    
    if(strcmp(gameState,"menu")==0){

        sceneMenu_mousewheel(pY);

    }else if(strcmp(gameState,"gameplay")==0){
        
        sceneGame_mousewheel(pY);

    }else if(strcmp(gameState,"gameover")==0){

    }

}