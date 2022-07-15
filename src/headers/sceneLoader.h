#include <stdio.h>
#include <stdbool.h>

void sceneLoader_load();

void sceneLoader_init(char pGameState[]);

void sceneLoader_update(float dt);

void sceneLoader_draw();

void sceneLoader_keypressed(SDL_Scancode pKey);

void sceneLoader_mousepressed(Uint8 pBtn,int pX, int pY);

void sceneLoader_mousemoved(int pX, int pY);

void sceneLoader_mousewheel(int pY);