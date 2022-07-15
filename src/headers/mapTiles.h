#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

void mapTiles_init(int pX,int pY);

void mapTiles_setImage(SDL_Texture *pImgMap,SDL_Texture *pImgIconsTiles,SDL_Texture *pImgIconsIndex,SDL_Texture *pImgIcons);

void mapTiles_resetValueIcon(bool pbIsIconBuildingActive);

int mapTiles_getCurrentTile();

int mapTiles_getTileId(int pLin,int pCol);

void mapTiles_setTileId(int pLin,int pCol,int pNewId);

void mapTiles_update(float dt);

static bool mapTiles_collideBuilding(int pX,int pY); 

static int mapTiles_getContact(int pLin,int pCol, int pId);

static int mapTiles_getNumContact(int pCol,int pNum);

static SDL_Rect mapTiles_getTile(int pNum,int pLine);

void mapTiles_draw(SDL_Renderer *pRenderer);

void mapTiles_mousepressed(Uint8 pBtn,int pX,int pY);

void mapTiles_mousemoved(int pX,int pY);

void mapTiles_keypressed(SDL_Scancode pKey);

void mapTiles_mousewheel(int pY);