#include "headers/graphics.h"

typedef struct Text Text;
struct Text{
    SDL_Texture *texture;
    SDL_Surface *surface;

    SDL_Color color;
    char text[255];
};


static int nbText=0;
static Text lstText[100];


SDL_Texture *graphics_newImage(SDL_Renderer *pRenderer,char pPath[]){
    
    SDL_Texture *texture=IMG_LoadTexture(pRenderer,pPath);

    if(texture==NULL){
        printf("Unable to create texture %s \n",IMG_GetError());
    }
    

    return texture;
}


void graphics_draw(SDL_Renderer *pRenderer,SDL_Texture *pTexture,int pX,int pY){

    int wTex,hTex;

    SDL_QueryTexture(pTexture,NULL,NULL,&wTex,&hTex);

    SDL_Rect rectTex={pX,pY,wTex,hTex};
    SDL_RenderCopy(pRenderer,pTexture,NULL,&rectTex);
}

void graphics_rectangle(SDL_Renderer *pRenderer,char pType[],int pX, int pY,int pW, int pH ,Uint8 pColor[]){

    SDL_Rect rect={pX,pY,pW,pH};
    
    if(pColor!=NULL){
        SDL_SetRenderDrawColor(pRenderer,pColor[0],pColor[1],pColor[2],pColor[3]);
        SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
    }else{
        SDL_SetRenderDrawColor(pRenderer,255,255,255,255);
    }

    if(strcmp(pType,"fill")==0){
        SDL_RenderFillRect(pRenderer,&rect);
    }else{
        SDL_RenderDrawRect(pRenderer,&rect);
    }


}


void graphics_line(SDL_Renderer *pRenderer,int pX1, int pY1, int pX2, int pY2, Uint8 pColor[]){

    if(pColor!=NULL){
        SDL_SetRenderDrawColor(pRenderer,pColor[0],pColor[1],pColor[2],pColor[3]);
    }else{
        SDL_SetRenderDrawColor(pRenderer,255,255,255,255);
    }

    SDL_RenderDrawLine(pRenderer,pX1,pY1,pX2,pY2);

}

TTF_Font *graphics_newFont(char pPath[], int pSizeFont){
    
    TTF_Font *font=NULL;
    font=TTF_OpenFont(pPath,pSizeFont);

    return font;
}


SDL_Texture *graphics_newText(SDL_Renderer *pRenderer,TTF_Font *pFont,char pText[],Uint8 pColor[]){
    
    SDL_Color color;
    SDL_Texture *texture=NULL;

    if(pColor!=NULL){
        
        color.r=pColor[0];
        color.g=pColor[1];
        color.b=pColor[2];
        color.a=pColor[3];

    }else{
        color.r=255;
        color.g=255;
        color.b=255;
        color.a=255;
    }

    if(pFont!=0){
        SDL_Surface *textSurface=TTF_RenderText_Blended(pFont,pText,color);
        texture=SDL_CreateTextureFromSurface(pRenderer,textSurface);

        SDL_FreeSurface(textSurface);
        TTF_CloseFont(pFont);

        Text myText;
        myText.texture=texture;
        myText.surface=textSurface;
        
        myText.color.r=color.r;
        myText.color.g=color.g;
        myText.color.b=color.b;
        myText.color.a=color.a;

        strcpy(myText.text,pText);

        lstText[nbText]=myText;
        nbText+=1;
    }

    return texture;
}



void graphics_drawText(SDL_Renderer *pRenderer,SDL_Texture *pTexture,int pX,int pY){

    SDL_Rect position;

    position.x=pX;
    position.y=pY;

    SDL_QueryTexture(pTexture,NULL,NULL,&position.w,&position.h);
    SDL_RenderCopy(pRenderer,pTexture,NULL,&position);

}

void graphics_deleteTexture(){

    for(int i=0;i<nbText;i++){
        Text myText=lstText[i];

        SDL_DestroyTexture(myText.texture);
    }


}




