#include "headers/GUIManager.h"

typedef struct GUI GUI;
struct GUI{

    SDL_Texture *img;
    SDL_Texture *lstImg[3];

    int x;
    int y;
    int width;
    int height;

    int scale;

    float timerSpeed;
    float timer;

    bool bIsClick;
    bool bIsHover;

    char type[255];

    float ratioBar;
    float maxValue;

};

static int nbComponent=0;
static GUI lstComponent[200];


/////////////////////////////////////////TEXT/////////////////////////
void GUI_createText(SDL_Renderer *pRenderer,TTF_Font *pFont, char pText[],int pX,int pY,Uint8 pColor[]){

    GUI myText;
    
    myText.x=pX;
    myText.y=pY;

    myText.width=0;
    myText.height=0;

    myText.scale=1;

    myText.img=graphics_newText(pRenderer,pFont,pText,pColor);

    strcpy(myText.type,"text");
    
    lstComponent[nbComponent]=myText;
    nbComponent+=1;
}


/////////////////////////////////////////////////BUTTON//////////////////////////////
void GUI_createButton(SDL_Texture *pLstTexture[],int pX,int pY, int pScale){

    GUI myButton;

    myButton.x=pX;
    myButton.y=pY;

    myButton.scale=pScale;

    SDL_QueryTexture(pLstTexture[0],NULL,NULL,&myButton.width,&myButton.height);

    myButton.bIsClick=false;
    myButton.bIsHover=false;

    for(int i=0;i<3;i++){
        myButton.lstImg[i]=pLstTexture[i];
    }
    
    strcpy(myButton.type,"button");

    myButton.timerSpeed=0.2;
    myButton.timer=myButton.timerSpeed;
    
    lstComponent[nbComponent]=myButton;
    nbComponent+=1;
}


//////////////////////////////////////CHECKBOX/////////////////////////////
void GUI_createCheckBox(SDL_Texture *pLstTexture[],int pX,int pY, int pScale){
    
    GUI myCheckBox;

    myCheckBox.x=pX;
    myCheckBox.y=pY;

    myCheckBox.scale=pScale;

    SDL_QueryTexture(pLstTexture[0],NULL,NULL,&myCheckBox.width,&myCheckBox.height);

    myCheckBox.bIsClick=false;

    for(int i=0;i<2;i++){
        myCheckBox.lstImg[i]=pLstTexture[i];
    }
    
    strcpy(myCheckBox.type,"checkBox");
    
    lstComponent[nbComponent]=myCheckBox;
    nbComponent+=1;
}


///////////////////////////////////PROGRESS BAR//////////////////////////////
void GUI_createProgressBar(SDL_Texture *pLstTexture[],int pX,int pY,int pScale,float pMaxValue){

    GUI myProgressBar;

    myProgressBar.x=pX;
    myProgressBar.y=pY;

    myProgressBar.scale=pScale;

    SDL_QueryTexture(pLstTexture[0],NULL,NULL,&myProgressBar.width,&myProgressBar.height);

    for(int i=0;i<2;i++){
        myProgressBar.lstImg[i]=pLstTexture[i];
    }

    myProgressBar.ratioBar=0;
    myProgressBar.maxValue=pMaxValue;
    
    strcpy(myProgressBar.type,"progressBar");
    
    lstComponent[nbComponent]=myProgressBar;
    nbComponent+=1;

}


///////////////////////////////////////////////PANEL////////////////////////////////
void GUI_createPanel(SDL_Texture *pTexture,int pX, int pY, int pScale){

    GUI myPanel;
    
    myPanel.img=pTexture;

    myPanel.x=pX;
    myPanel.y=pY;
    myPanel.scale=pScale;

    SDL_QueryTexture(pTexture,NULL,NULL,&myPanel.width,&myPanel.height);

    strcpy(myPanel.type,"panel");

    lstComponent[nbComponent]=myPanel;
    nbComponent+=1;

}


/////update////
void GUI_update(float dt,float pValueProgress){

    for(int i=0;i<nbComponent;i++){

        GUI *myComponent;
        myComponent=&lstComponent[i];

        if(strcmp(myComponent->type,"button")==0){
            
            if(myComponent->bIsClick){
                myComponent->timer-=dt;

                if(myComponent->timer<=0){
                    myComponent->timer=myComponent->timerSpeed;

                    myComponent->bIsClick=false;
                    myComponent->bIsHover=true;
                }
            }

        }else if(strcmp(myComponent->type,"progressBar")==0 && pValueProgress!=-1){

            myComponent->ratioBar=pValueProgress/myComponent->maxValue;

        }

    }

}


/////draw///
void GUI_draw(SDL_Renderer *pRenderer){
    
    for(int i=0;i<=nbComponent;i++){

        GUI *myComponent;
        myComponent=&lstComponent[i];

        SDL_Rect rectComponent={myComponent->x,myComponent->y,myComponent->width*myComponent->scale,
                myComponent->height*myComponent->scale};

        ///////PANEL//////////////////////////

        if(strcmp(myComponent->type,"panel")==0){

            SDL_RenderCopy(pRenderer,myComponent->img,NULL,&rectComponent);
        

        /////////////////////////////TEXT////////////////

        }else if(strcmp(myComponent->type,"text")==0){

            graphics_drawText(pRenderer,myComponent->img,myComponent->x,myComponent->y);


        //////////////////////////////BUTTON///////////////////

        }else if(strcmp(myComponent->type,"button")==0){

            ////no click and no hover
            if(!myComponent->bIsClick && !myComponent->bIsHover){
                
                SDL_RenderCopy(pRenderer,myComponent->lstImg[0],NULL,&rectComponent);

            ///no click and hover
            }else if(!myComponent->bIsClick && myComponent->bIsHover){
                
                SDL_RenderCopy(pRenderer,myComponent->lstImg[1],NULL,&rectComponent);

            ///no hover and click
            }else if(myComponent->bIsClick && !myComponent->bIsHover){

                SDL_RenderCopy(pRenderer,myComponent->lstImg[2],NULL,&rectComponent);

            }


        //////////////////////////////////////////CHECKBOX////////////////

        }else if(strcmp(myComponent->type,"checkBox")==0){
            
            if(!myComponent->bIsClick){
                
                SDL_RenderCopy(pRenderer,myComponent->lstImg[0],NULL,&rectComponent);

            }else{
                
                SDL_RenderCopy(pRenderer,myComponent->lstImg[1],NULL,&rectComponent);
            
            }
            

        }else if(strcmp(myComponent->type,"progressBar")==0){

            SDL_RenderCopy(pRenderer,myComponent->lstImg[0],NULL,&rectComponent);

            SDL_Rect rectProgress={myComponent->x,myComponent->y,(myComponent->width*myComponent->scale)*myComponent->ratioBar,myComponent->height*myComponent->scale};
            SDL_RenderCopy(pRenderer,myComponent->lstImg[1],NULL,&rectProgress);
        
        }

    }

}


/////mousepressed
void GUI_mousepressed(Uint8 pBtn,int pX, int pY){
  
    for(int i=0;i<nbComponent;i++){
        GUI *myComponent;
        myComponent=&lstComponent[i];

        bool bCollide=utils_checkCollision(myComponent->x,myComponent->y,myComponent->width,myComponent->height,
                                            pX,pY,1,1);


        if(strcmp(myComponent->type,"button")==0){
           
            if(bCollide){
                ////click
                if(myComponent->bIsHover && !myComponent->bIsClick){
                    
                    myComponent->bIsHover=false;
                    myComponent->bIsClick=true;

                    return;

                }
                
            }

        }else if(strcmp(myComponent->type,"checkBox")==0){

            if(bCollide){

                if(!myComponent->bIsClick){
                    
                    myComponent->bIsClick=true;
                    return;

                }else{
                    
                    myComponent->bIsClick=false;
                    return;
                }

            }

        }

    }

}


////mousemove
void GUI_mousemoved(int pX, int pY){

    for(int i=0;i<nbComponent;i++){

        GUI *myComponent;
        myComponent=&lstComponent[i];

        bool bCollide=utils_checkCollision(myComponent->x,myComponent->y,myComponent->width,myComponent->height,
                                            pX,pY,1,1);


        if(strcmp(myComponent->type,"button")==0){

            if(bCollide){
                ////hover
                if(!myComponent->bIsHover && !myComponent->bIsClick){
                    myComponent->bIsHover=true;
                }
                
            }else{
                ////no hover
               
                myComponent->bIsHover=false;
                myComponent->bIsClick=false;
                
            }

        }

        
    }

}