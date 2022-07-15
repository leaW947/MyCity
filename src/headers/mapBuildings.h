#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


void mapBuildings_init();

void mapBuildings_setImages(SDL_Texture *pImgHomes,SDL_Texture *pImgBuildings,SDL_Texture *pImgBuildingsDollars,SDL_Texture *pImgIconsIndex, SDL_Texture *pImgIcons,
SDL_Texture *pImgBubble,SDL_Texture *pImgMoney);

void mapBuildings_resetIconValue(bool pbIsIconTileActive);

static void mapBuildings_reverseBuilding();

static float mapBuildings_getPriceBuilding(char pName[]);

SDL_Rect mapBuildings_getRectBuilding(int pId, int pNum);

int mapBuildings_getNbBuilding();

static void mapBuildings_addBuilding(char pName[],char pType[]);

static void mapBuildings_addMoney(int pX,int pY,int pMoney,int pTimerSpeed,int pId);

static void mapBuildings_reloadLosangePos(int pX,int pY);

void mapBuildings_delete(int pId);

static void mapBuildings_moveBuilding();

static int mapBuildings_compare(const void *a,const void *b);

static void mapBuildings_sortBuldingZ_order();

void mapBuildings_update(float dt);

static void mapBuildings_drawBubble(SDL_Renderer *pRenderer);

void mapBuildings_draw(SDL_Renderer *pRenderer);

void mapBuildings_mousepressed(Uint8 pBtn,int pX,int pY);

void mapBuildings_keypressed(SDL_Scancode pKey);

void mapBuildings_mousewheel(int pY);

void mapBuildings_mousemoved(int pX,int pY);