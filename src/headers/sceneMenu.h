#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


void sceneMenu_load();

void sceneMenu_update(float dt);

void sceneMenu_draw();

void sceneMenu_keypressed(SDL_Scancode pKey);

void sceneMenu_mousepressed(Uint8 pBtn, int pX,int pY);

void sceneMenu_mousemoved(int pX,int pY);

void sceneMenu_mousewheel(int pY);