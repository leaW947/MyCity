#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


void fireManager_load(SDL_Texture *pImgTiles,SDL_Texture *pImgIconFire,SDL_Texture *pImgFireAnim);

static void fireManager_collideBuilding(int pLin,int pCol);

static void fireManager_collideTileId2(int pLin,int pCol);

void fireManager_update(float dt);

void fireManager_draw(SDL_Renderer *pRenderer);

static void fireManager_cancelTileFire();

void fireManager_mousepressed(Uint8 pBtn,int pX,int pY);