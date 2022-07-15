#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


void assetManager_addImage(SDL_Renderer *pRenderer, char pPath[]);

SDL_Texture *assetManager_getImage(char pPath[]);

void assetManager_addSound(char pPath[],char pType[]);

Mix_Chunk *assetManager_getSound(char pPath[]);

Mix_Music *assetManager_getMusic(char pPath[]);

void assetManager_deleteAssets();