#include "headers/fireManager.h"

typedef struct Fire Fire;
struct Fire{

    float timerSpeed;
    float timer;

    int cTilePath;
    int lTilePath;

    int cOldTilePath;
    int lOldTilePath;

    float timerFrameSpeed;
    float timerFrame;
    int frameAnim;

    bool bOn;

};

typedef struct IconFire IconFire;
struct IconFire{

    bool bIsActive;

    int xScreen;
    int yScreen;
};


static const int MAP_FIRE_WIDTH=8*4;
static const int MAP_FIRE_HEIGHT=8*5;

static int MAP_FIRE_X=0;
static int MAP_FIRE_Y=0;

static int mapFire[8*5][8*4];

static SDL_Texture *imgIconFire;
static SDL_Texture *imgTiles;
static SDL_Texture *imgFireAnim;

static IconFire iconFire;
static Fire currentFire;

static float timerSpeedFire;
static float timerFire;

static int nbExplore;

void fireManager_load(SDL_Texture *pImgTiles,SDL_Texture *pImgIconFire,SDL_Texture *pImgFireAnim){

    timerSpeedFire=0.2;
    timerFire=timerSpeedFire;

    nbExplore=0;

    imgIconFire=pImgIconFire;
    imgTiles=pImgTiles;
    imgFireAnim=pImgFireAnim;

    ////current fire
    currentFire.cTilePath=-1;
    currentFire.lTilePath=-1;

    currentFire.timerSpeed=utils_random(60,60*10);
    currentFire.timer=currentFire.timerSpeed;

    currentFire.timerFrameSpeed=0.1;
    currentFire.timerFrame=currentFire.timerFrameSpeed;
    currentFire.frameAnim=0;


    ////icon fire
    iconFire.bIsActive=false;

    iconFire.xScreen=gameplayService_screenWidth-(TILESIZE*2);
    iconFire.yScreen=gameplayService_screenHeight-(TILESIZE*2);


    ////Map fire

    for(int l=0;l<MAP_FIRE_HEIGHT;l++){

        for(int c=0;c<MAP_FIRE_WIDTH;c++){

            mapFire[l][c]=0;

        }

    }


}


static void  fireManager_collideBuilding(int pLin,int pCol){

    int x=(pCol-pLin)*(TILESIZE*scaleMap)+MAP_X;
    int y=(pLin+pCol)*((TILESIZE/2)*scaleMap)+MAP_Y;

    for(int n=mapBuildings_getNbBuilding();n>-1;n--){

        SDL_Rect rectCollideBuilding1=mapBuildings_getRectBuilding(n,1);
        SDL_Rect rectCollideBuilding2=mapBuildings_getRectBuilding(n,2);

        bool bCollideBuilding1=utils_checkCollision(rectCollideBuilding1.x,rectCollideBuilding1.y,
        rectCollideBuilding1.w,rectCollideBuilding1.h,x,y,(TILESIZE*2)*scaleMap,TILESIZE);

        bool bCollideBuilding2=utils_checkCollision(rectCollideBuilding2.x,rectCollideBuilding2.y,
        rectCollideBuilding2.w,rectCollideBuilding2.h,x,y,(TILESIZE*2)*scaleMap,TILESIZE);

        if(bCollideBuilding1 || bCollideBuilding2){
        
 
            ///////////tiles collide with building 
            for(int l=0;l<MAP_FIRE_HEIGHT;l++){

                for(int c=0;c<MAP_FIRE_WIDTH;c++){

                    int xTile=(c-l)*(TILESIZE*scaleMap)+MAP_X;
                    int yTile=(l+c)*((TILESIZE/2)*scaleMap)+MAP_Y;

                    bool bCollideTileBuilding1=utils_checkCollision(rectCollideBuilding1.x,rectCollideBuilding1.y,
                    rectCollideBuilding1.w,rectCollideBuilding1.h,xTile,yTile,(TILESIZE*2)*scaleMap,TILESIZE);

                    bool bCollideTileBuilding2=utils_checkCollision(rectCollideBuilding2.x,rectCollideBuilding2.y,
                    rectCollideBuilding2.w,rectCollideBuilding2.h,xTile,yTile,(TILESIZE*2)*scaleMap,TILESIZE);

                    if(bCollideTileBuilding1 || bCollideTileBuilding2){
                        
                        if(mapFire[l][c]==0){
                            
                            currentFire.cTilePath=c;
                            currentFire.lTilePath=l;
                            mapFire[l][c]=1;
                        }
                        
                    }
                }
            }

            mapBuildings_delete(n);
            return;

        }

    
        
    }
}


static void fireManager_collideTileId2(int pLin,int pCol){
    
    int x=(pCol-pLin)*(TILESIZE*scaleMap)+MAP_X;
    int y=(pLin+pCol)*((TILESIZE/2)*scaleMap)+MAP_Y;

    int id=mapFire[pLin][pCol];

    for(int l=0;l<MAP_FIRE_HEIGHT;l++){

        for(int c=0;c<MAP_FIRE_WIDTH;c++){

            int idTile=mapFire[l][c];

            int xTile=(c-l)*(TILESIZE*scaleMap)+MAP_X;
            int yTile=(l+c)*((TILESIZE/2)*scaleMap)+MAP_Y;

            if(idTile==2 && id==1){
                SDL_Rect rectCollideTile={x,y,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap};
                SDL_Rect rectCollideTileId2={xTile,yTile,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap};

                bool bCollideTile=utils_checkCollision(rectCollideTile.x,rectCollideTile.y,
                rectCollideTile.w,rectCollideTile.h,rectCollideTileId2.x,rectCollideTileId2.y,
                rectCollideTileId2.w,rectCollideTileId2.h);

                if(bCollideTile){
                    currentFire.cTilePath=c;
                    currentFire.lTilePath=l;
                    mapFire[l][c]=1;
                }
            }
        }
    }


}


void fireManager_update(float dt){

    if(!currentFire.bOn){
        currentFire.timer-=dt;

        if(currentFire.timer<=0){
            
            currentFire.timerSpeed=utils_random(60,60*10);
            currentFire.timer=currentFire.timerSpeed;
            
            currentFire.bOn=true;
            nbExplore=0;
            
            currentFire.lTilePath=utils_random(0,MAP_FIRE_HEIGHT);
            currentFire.cTilePath=utils_random(0,MAP_FIRE_WIDTH);
            mapFire[currentFire.lTilePath][currentFire.cTilePath]=1;

        }

    }else{

        /////////////frame animation fire
        currentFire.timerFrame-=dt;

        if(currentFire.timerFrame<=0){
            currentFire.timerFrame=currentFire.timerFrameSpeed;

            if(currentFire.frameAnim<2){
                currentFire.frameAnim+=1;
            }else{
                currentFire.frameAnim=0;
            }
        }

        //////////////fire/////
        timerFire-=dt;

        if(timerFire<=0){

            currentFire.cOldTilePath=currentFire.cTilePath;
            currentFire.lOldTilePath=currentFire.lTilePath;

            timerFire=timerSpeedFire;

            int nbDirection=0;
            char lstDirection[4][10];

            ////UP
            if(currentFire.lTilePath>0){

                
                if(mapTiles_getTileId(currentFire.lTilePath-1,currentFire.cTilePath)!=3){

                    strcpy(lstDirection[nbDirection],"up");
                    nbDirection+=1;

                }

            }

            ///DOWN
            if(currentFire.lTilePath<MAP_FIRE_HEIGHT){

                if(mapTiles_getTileId(currentFire.lTilePath+1,currentFire.cTilePath)!=3){

                    strcpy(lstDirection[nbDirection],"down");
                    nbDirection+=1;

                }
               
            }

            ////LEFT
            if(currentFire.cTilePath>0){

                if(mapTiles_getTileId(currentFire.lTilePath,currentFire.cTilePath-1)!=3){

                    strcpy(lstDirection[nbDirection],"left");
                    nbDirection+=1;

                }

            }

            ////RIGHT
            if(currentFire.cTilePath<MAP_FIRE_WIDTH){

                if(mapTiles_getTileId(currentFire.lTilePath,currentFire.cTilePath+1)!=3){

                    strcpy(lstDirection[nbDirection],"right");
                    nbDirection+=1;

                }

            }

            int rndDirection=utils_random(0,nbDirection);
            timerFire=timerSpeedFire;

            if(strcmp(lstDirection[rndDirection],"up")==0){

                currentFire.lTilePath-=1;

            }else if(strcmp(lstDirection[rndDirection],"down")==0){

                currentFire.lTilePath+=1;
        
            }else if(strcmp(lstDirection[rndDirection],"right")==0){

                currentFire.cTilePath+=1;

            }else if(strcmp(lstDirection[rndDirection],"left")==0){

                currentFire.cTilePath-=1;

            }

            mapFire[currentFire.lTilePath][currentFire.cTilePath]=1;

            fireManager_collideBuilding(currentFire.lTilePath,currentFire.cTilePath);
            fireManager_collideTileId2(currentFire.lTilePath,currentFire.cTilePath);
    
        }

    }
        
}

void fireManager_draw(SDL_Renderer *pRenderer){

    for(int l=0;l<MAP_FIRE_HEIGHT;l++){

        for(int c=0;c<MAP_FIRE_WIDTH;c++){

            int id=mapFire[l][c];

            int x=(c-l)*(TILESIZE*scaleMap)+MAP_X;
            int y=(l+c)*((TILESIZE/2)*scaleMap)+MAP_Y;

            if(id!=0){
                SDL_Rect srRect={2*(TILESIZE*2),3*TILESIZE,TILESIZE*2,TILESIZE};
                SDL_Rect dsRect={x,y,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap};

                SDL_RenderCopy(pRenderer,imgTiles,&srRect,&dsRect);

                if(currentFire.bOn && id==1){

                    SDL_Rect srRectAnim={currentFire.frameAnim*TILESIZE,0,TILESIZE,TILESIZE};
                    SDL_Rect dsRectAnim={x,y-((TILESIZE*1.5)*scaleMap),(TILESIZE*2)*scaleMap,(TILESIZE*2)*scaleMap};

                    SDL_RenderCopy(pRenderer,imgFireAnim,&srRectAnim,&dsRectAnim);

                }

            }


        }

    }

    if(currentFire.bOn){
        SDL_Rect rectSrIcon={0,0,TILESIZE,TILESIZE};
        SDL_Rect rectDsIcon={iconFire.xScreen,iconFire.yScreen,TILESIZE*2,TILESIZE*2};

        SDL_RenderCopy(pRenderer,imgIconFire,&rectSrIcon,&rectDsIcon);
    }

}

static void fireManager_cancelTileFire(){
    
    for(int l=0;l<MAP_FIRE_HEIGHT;l++){

        for(int c=0;c<MAP_FIRE_WIDTH;c++){

            if(mapFire[l][c]==1){
                mapFire[l][c]=2;
            }

        }
    }

}

void fireManager_mousepressed(Uint8 pBtn,int pX,int pY){

    if(pBtn==1){

        if(currentFire.bOn){

            bool bCollideIcon=utils_checkCollision(pX,pY,1,1,iconFire.xScreen,iconFire.yScreen,
            TILESIZE*2,TILESIZE*2);

            if(bCollideIcon){
                currentFire.bOn=false;
                fireManager_cancelTileFire();
                
                return;
            }

        }else{
            
            for(int l=0;l<MAP_FIRE_HEIGHT;l++){

                for(int c=0;c<MAP_FIRE_WIDTH;c++){

                    int x=(c-l)*(TILESIZE*scaleMap)+MAP_X;
                    int y=(l+c)*((TILESIZE/2)*scaleMap)+MAP_Y;
                    
                    //////////calcul tile iso////////
                    float xMouse=pX-(MAP_X+(TILESIZE*scaleMap));
                    float yMouse=pY-MAP_Y;

                    float cTile=xMouse/(TILESIZE*scaleMap);
                    float lTile=yMouse/((TILESIZE/2)*scaleMap);

                    int line=abs((lTile-cTile)/2);
                    int column=abs((cTile+lTile)/2);

                    ///////id 2D//////
                    int id=mapFire[line][column];

                    /////////collide with tile 3D iso////
                    bool bCollide=utils_checkCollision(pX,pY,1,1,x,y,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap);
                    int currentTile=mapTiles_getCurrentTile();

                    if(id!=0 && bCollide && currentTile==0){
                        mapFire[line][column]=0;

                        if(mapTiles_getTileId(line,column)>0){
                            mapTiles_setTileId(line,column,0);
                        }
                    }
                }
            }

        }

    }

}