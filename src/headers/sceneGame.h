#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

void sceneGame_load();

void sceneGame_update(float dt);

void sceneGame_draw();

void sceneGame_keypressed(SDL_Scancode pKey);

void sceneGame_mousepressed(Uint8 pBtn, int pX,int pY);

void sceneGame_mousemoved(int pX,int pY);

void sceneGame_mousewheel(int pY);