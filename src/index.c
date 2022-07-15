#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "main.c"

int main(int argc,char *argv[]){

    int screenWidth=1200;
    int screenHeight=600;

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){

        printf("Unable to initialize SDL %s \n",SDL_GetError());
        return -1;

    }


    ///window
    SDL_Window *window=SDL_CreateWindow(
        "Title program",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth,screenHeight,
        SDL_WINDOW_SHOWN
    );

    if(window==NULL){
        
        printf("Unable to create window %s \n",SDL_GetError());
        return -1;

    }

    ////renderer
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer==NULL){
        
        printf("Unable to create renderer %s \n",SDL_GetError());
        return -1;

    }else{

        int imgFlags=IMG_INIT_PNG | IMG_INIT_JPG;
        
        //////////IMG

        if(!(IMG_Init(imgFlags) & imgFlags)){
            
            printf("Unable to initialize SDL image %s \n", IMG_GetError());
            return -1;

        }

        ///ttf
        if(TTF_Init()!=0){

            printf("Unable to initialize SDL ttf %s \n",TTF_GetError());
            return -1;

        }

        
          ///audio
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)!=0){
            printf("Unable to initialize SDL mixer %s \n",Mix_GetError());
            return -1;

        }

    }

    //////////gameloop/////////////

    bool bOnRun=true;
    float oldTime=0;

    load(renderer,screenWidth,screenHeight);

    while(bOnRun){

        float newTime=SDL_GetTicks();
        float dt=fabs((oldTime-newTime)/1000);
        oldTime=newTime;

        SDL_Event event;

        if(SDL_PollEvent(&event)){
            
            if(event.type==SDL_QUIT){
                bOnRun=false;
                break;

            }else if(event.type==SDL_KEYDOWN){

                keypressed(event.key.keysym.scancode);

            }else if(event.type==SDL_MOUSEBUTTONDOWN){

                mousepressed(event.button.button,event.motion.x,event.motion.y);

            }else if(event.type==SDL_MOUSEMOTION){
                mousemoved(event.motion.x,event.motion.y);
            
            }else if(event.type==SDL_MOUSEWHEEL){
                
                mousewheel(event.wheel.y);

            }

        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        update(dt);
        draw();

        SDL_RenderPresent(renderer);

        SDL_Delay(10);

    }

    deleteAsset();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}