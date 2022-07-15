#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


void GUI_createText(SDL_Renderer *pRenderer,TTF_Font *pFont, char pText[],int pX,int pY,Uint8 pColor[]);

void GUI_createButton(SDL_Texture *pLstTexture[],int pX,int pY, int pScale);

void GUI_createCheckBox(SDL_Texture *pLstTexture[],int pX,int pY, int pScale);

void GUI_createProgressBar(SDL_Texture *pLstTexture[],int pX,int pY,int pScale,float pMaxValue);

void GUI_createPanel(SDL_Texture *pTexture,int pX, int pY,int pScale);

void GUI_update(float dt,float pValueProgress);

void GUI_draw(SDL_Renderer *pRenderer);

void GUI_mousepressed(Uint8 pBtn,int pX, int pY);

void GUI_mousemoved(int pX, int pY);
