#include "headers/assetManager.h"

#include "graphics.c"

////struct Image
typedef struct Image Image;
struct Image{

    SDL_Texture *texture;
    char path[255];

};


///struct Sound
typedef struct Sound Sound;
struct Sound{
    Mix_Music *music;
    Mix_Chunk *sound;
    char path[255];
    char type[100];
};


static int nbImg=0;
static Image lstImage[500];

static int nbSound=0;
static Sound lstSound[500];

void assetManager_addImage(SDL_Renderer *pRenderer, char pPath[]){

    SDL_Texture *texImg=graphics_newImage(pRenderer,pPath);
    
    Image img;
    img.texture=texImg;
    strcpy(img.path,pPath);

    lstImage[nbImg]=img;
    nbImg+=1;
}


SDL_Texture *assetManager_getImage(char pPath[]){

    for(int i=0;i<nbImg;i++){

        Image myImage=lstImage[i];

        if(strcmp(myImage.path,pPath)==0){
            return myImage.texture;
        }

    }

    return NULL;
}


void assetManager_addSound(char pPath[], char pType[]){
    
    Sound mySound;

    if(strcmp(pType,"music")==0){

        Mix_Music *music=Mix_LoadMUS(pPath);

        mySound.music=music;
        mySound.sound=NULL;

    }else if(strcmp(pType,"sound")==0){

        Mix_Chunk *sound=Mix_LoadWAV(pPath);

        mySound.music=NULL;
        mySound.sound=sound;

    }
    
    strcpy(mySound.path,pPath);
    strcpy(mySound.type,pType);

    lstSound[nbSound]=mySound;
    nbSound+=1;

}


Mix_Music *assetManager_getMusic(char pPath[]){

    for(int i=0;i<nbSound;i++){

        Sound mySound=lstSound[i];

        if(strcmp(mySound.path,pPath)==0 && strcmp(mySound.type,"music")==0){
            return mySound.music;
        }
    }

    return NULL;
}

Mix_Chunk *assetManager_getSound(char pPath[]){

    for(int i=0;i<nbSound;i++){

        Sound mySound=lstSound[i];

        if(strcmp(mySound.path,pPath)==0 && strcmp(mySound.type,"sound")==0){
            return mySound.sound;
        }
    }

    return NULL;

}


void assetManager_deleteAssets(){
    
    ///images
    for(int i=0;i<nbImg;i++){
        
        Image myImage=lstImage[i];

        SDL_DestroyTexture(myImage.texture);

    }

    ///sounds
    for(int i=0;i<nbSound;i++){

        Sound mySound=lstSound[i];

        if(strcmp(mySound.type,"music")==0){
            
            Mix_FreeMusic(mySound.music);

        }else if(strcmp(mySound.type,"sound")==0){

            Mix_FreeChunk(mySound.sound);

        }

    }

}