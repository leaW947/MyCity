#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


SDL_Texture *graphics_newImage(SDL_Renderer *pRenderer,char pPath[]);

void graphics_draw(SDL_Renderer *pRenderer,SDL_Texture *pTexture,int pX,int pY);

void graphics_rectangle(SDL_Renderer *pRenderer,char pType[],int pX, int pY,int pW, int pH, Uint8 pColor[]);

void graphics_line(SDL_Renderer *pRenderer,int pX1, int pY1, int pX2, int pY2, Uint8 pColor[]);

TTF_Font *graphics_newFont(char pPath[], int pSizeFont);

SDL_Texture *graphics_newText(SDL_Renderer *pRenderer,TTF_Font *pFont,char pText[],Uint8 pColor[]);

void graphics_drawText(SDL_Renderer *pRenderer,SDL_Texture *pTexture,int pX,int pY);

void graphics_deleteTexture();