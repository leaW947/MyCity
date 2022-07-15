#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

void mapManager_load();

void mapManager_draw(SDL_Renderer *pRenderer);

void mapManager_update(float dt);

void mapManager_mousepressed(Uint8 pBtn,int pX,int pY);

void mapManager_mousemoved(int pX,int pY);

void mapManager_keypressed(SDL_Scancode pKey);

void mapManager_mousewheel(int pY);