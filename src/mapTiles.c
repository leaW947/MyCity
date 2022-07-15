#include "headers/mapTiles.h"

#include "headers/mapBuildings.h"
#include "headers/fireManager.h"

typedef struct Icon Icon;
struct Icon{

    char type[255];
    SDL_Rect rect;
    SDL_Rect rectActive;
    int xScreen;
    int yScreen;
    float scale;
    bool bIsActive;
    bool bIsVisible;

};

float scaleMap=0.5;
const int TILESIZE=32;

static bool bOnTile=true;

static const int MAP_WIDTH=8*4;
static const int MAP_HEIGHT=8*5;

static int MAP_X;
static int MAP_Y;

static int INITIAL_X;
static int INITIAL_Y;

static const int MAP_SPEED=5;

static SDL_Texture *mapImg=NULL;
static SDL_Texture *mapImgIcons=NULL;
static SDL_Texture *imgIconsIndex=NULL;
static SDL_Texture *imgIcons=NULL;

static int mapData[8*5][8*4];

static int nbIconTile=6;
static int nbTile=(11*3)+2;

static Icon lstIcon[6];

static int currentTile=-1;
static bool bOnIcon=false;

void mapTiles_init(int pX,int pY){

    MAP_X=pX;
    MAP_Y=pY;

    INITIAL_X=pX;
    INITIAL_Y=pY;

    ///////////////map/////////////
    for(int l=0;l<MAP_HEIGHT;l++){
        
        for(int c=0;c<MAP_WIDTH;c++){

            mapData[l][c]=0;
        }

    }


    /////////////////////////icon/////////////////////

    for(int n=0;n<nbIconTile;n++){

        if(n<4){
            ///////////////img icons tiles////////////
            int l=0;
            int c=n;

            int x=c*TILESIZE;
            int y=l*TILESIZE;

            lstIcon[n].rect.x=x;
            lstIcon[n].rect.y=y;
            lstIcon[n].rect.w=TILESIZE;
            lstIcon[n].rect.h=TILESIZE;

            lstIcon[n].rectActive.x=x;
            lstIcon[n].rectActive.y=y+TILESIZE;
            lstIcon[n].rectActive.w=TILESIZE;
            lstIcon[n].rectActive.h=TILESIZE;

            lstIcon[n].scale=2;

            lstIcon[n].bIsActive=false;
            lstIcon[n].bIsVisible=false;

            lstIcon[n].xScreen=10+(TILESIZE*2)+(n*((TILESIZE*2)+10));
            lstIcon[n].yScreen=gameplayService_screenHeight-(TILESIZE*2.5);

            
            if(n==0){

                strcpy(lstIcon[n].type,"ROAD");

            }else if(n==1){
                
                strcpy(lstIcon[n].type,"DIRT_ROAD");

            }else if(n==2){
                
                strcpy(lstIcon[n].type,"WATER_ROAD");

            }else if(n==3){
                
                strcpy(lstIcon[n].type,"DELETE");
            }

        
        }else if(n==4){
            
            ////////////img icons/////////

            int x=0*TILESIZE;
            int y=0*TILESIZE;

            lstIcon[n].rect.x=x;
            lstIcon[n].rect.y=y;
            lstIcon[n].rect.w=TILESIZE-11;
            lstIcon[n].rect.h=TILESIZE-11;

            lstIcon[n].rectActive.x=x;
            lstIcon[n].rectActive.y=y+(TILESIZE-11);
            lstIcon[n].rectActive.w=TILESIZE-11;
            lstIcon[n].rectActive.h=TILESIZE-11;

            lstIcon[n].scale=2;

            lstIcon[n].bIsActive=false;
            lstIcon[n].bIsVisible=false;
            
            lstIcon[n].yScreen=gameplayService_screenHeight-(TILESIZE*2.5);
            lstIcon[n].xScreen=0;

            strcpy(lstIcon[n].type,"CLOSE");


        }else if(n==5){
            
            ////////////////img icons index

            int x=2*TILESIZE;
            int y=0*TILESIZE;

            lstIcon[n].rect.x=x;
            lstIcon[n].rect.y=y;
            lstIcon[n].rect.w=TILESIZE;
            lstIcon[n].rect.h=TILESIZE;

            lstIcon[n].rectActive.x=x;
            lstIcon[n].rectActive.y=y+TILESIZE;
            lstIcon[n].rectActive.w=TILESIZE;
            lstIcon[n].rectActive.h=TILESIZE;

            lstIcon[n].scale=2;

            lstIcon[n].bIsActive=false;
            lstIcon[n].bIsVisible=true;

            lstIcon[n].xScreen=50;
            lstIcon[n].yScreen=gameplayService_screenHeight-(TILESIZE*2);

            strcpy(lstIcon[n].type,"OPEN");


        }

          
    }
}

void mapTiles_setImage(SDL_Texture *pImgMap,SDL_Texture *pImgIconsTiles,SDL_Texture *pImgIocnsIndex,SDL_Texture *pImgIcons){
    
    mapImg=pImgMap;
    mapImgIcons=pImgIconsTiles;
    imgIconsIndex=pImgIocnsIndex;
    imgIcons=pImgIcons;

}


void mapTiles_resetValueIcon(bool pbIsIconBuildingActive){

    for(int n=0;n<nbIconTile;n++){
        
        if(pbIsIconBuildingActive){
            
            lstIcon[n].bIsVisible=false;
            lstIcon[n].bIsActive=false;

        }else{

            if(n==5){
                
                lstIcon[n].bIsVisible=true;
                lstIcon[n].bIsActive=false;

            }
        
        }
    
    }

}

int mapTiles_getCurrentTile(){
    return currentTile;
}


int mapTiles_getTileId(int pLin,int pCol){
    return mapData[pLin][pCol];
}


void mapTiles_setTileId(int pLin,int pCol,int pNewId){
    mapData[pLin][pCol]=pNewId;
}


void mapTiles_update(float dt){

    //////////////////////////////////////ICON////////////

    /////////open/////////
    if(lstIcon[nbIconTile-1].bIsActive){
        lstIcon[nbIconTile-1].bIsVisible=false;
        lstIcon[nbIconTile-1].bIsActive=false;

        for(int i=0;i<nbIconTile-1;i++){
            lstIcon[i].bIsVisible=true;
        }

    //////////////close/////////
    }else if(lstIcon[nbIconTile-2].bIsActive){

        lstIcon[nbIconTile-1].bIsVisible=true;
        currentTile=-1;
    
        for(int i=0;i<nbIconTile-1;i++){
            lstIcon[i].bIsActive=false;
            lstIcon[i].bIsVisible=false;
        }

        mapBuildings_resetIconValue(false);


    }else{

        /////////////////////Tile change//////////////////
        
        ////ROAD///////
        if(lstIcon[0].bIsActive){
            
            lstIcon[0].scale=2.2;
            currentTile=1;

        }else{

            lstIcon[0].scale=2;

        }
        
        /////////DIRT ROAD///////
        if(lstIcon[1].bIsActive){
            
            lstIcon[1].scale=2.2;
            currentTile=2;

        }else{

            lstIcon[1].scale=2;

        }

        ///////////////////////WATER ROAD//////////        
        if(lstIcon[2].bIsActive){
            
            lstIcon[2].scale=2.2;
            currentTile=3;

        }else{

            lstIcon[2].scale=2;

        }
        
        ////////////////DELETE ROAD/////////
        if(lstIcon[3].bIsActive){
            
            lstIcon[3].scale=2.2;
            currentTile=0;

        }else{

            lstIcon[3].scale=2;

        }


    }

}


static bool mapTiles_collideBuilding(int pX,int pY){

    for(int n=mapBuildings_getNbBuilding();n>-1;n--){

        SDL_Rect rectCollideTile={pX,pY,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap};

        SDL_Rect rectCollide1=mapBuildings_getRectBuilding(n,1);
        SDL_Rect rectCollide2=mapBuildings_getRectBuilding(n,2);

        bool bCollide1=utils_checkCollision(rectCollide1.x,rectCollide1.y,rectCollide1.w,rectCollide1.h,
        rectCollideTile.x,rectCollideTile.y,rectCollideTile.w,rectCollideTile.h);

        bool bCollide2=utils_checkCollision(rectCollide2.x,rectCollide2.y,rectCollide2.w,rectCollide2.h,
            rectCollideTile.x,rectCollideTile.y,rectCollideTile.w,rectCollideTile.h);

        if(bCollide1 || bCollide2){
            return true;
        }
    }

    return false;

}


static int mapTiles_getContact(int pLin,int pCol,int pId){

    int numContact=0;

    /////////////////UP///////////////////
    if(pLin>0){

        if(mapData[pLin-1][pCol]==pId){
            numContact+=1;
        }

    }

    ////////////////////RIGHT////////////
    if(pCol<MAP_WIDTH){

        if(mapData[pLin][pCol+1]==pId){
            numContact+=2;
        }

    }

    //////////////DOWN////////////
    if(pLin<MAP_HEIGHT){

        if(mapData[pLin+1][pCol]==pId){
            numContact+=4;
        }

    }

    //////////////LEFT///////////
    if(pCol>0){

        if(mapData[pLin][pCol-1]==pId){
            numContact+=8;
        }

    }

    if(numContact==0){
        numContact=1;
    }

    return numContact;

}

static int mapTiles_getNumContact(int pCol, int pNum){

    int numContact=0;

    switch(pCol){

        case 0:

            if(pNum==2 || pNum==8 || pNum==10){
                numContact=pNum;
            }

            break;

        case 1:

            if(pNum==1 || pNum==4 || pNum==5){
                numContact=pNum;
            }

            break;

        case 2:

            if(pNum==9){
                numContact=pNum;
            }

            break;

        case 3:

            if(pNum==6){
                numContact=pNum;
            }

            break;

        case 4:

            if(pNum==3){
                numContact=pNum;
            }

            break;

        case 5:

            if(pNum==12){
                numContact=pNum;
            }

            break;

        case 6:

            if(pNum==15){
                numContact=pNum;
            }

            break;

        case 7:

            if(pNum==14){
                numContact=pNum;
            }

            break;

        case 8:

            if(pNum==11){
                numContact=pNum;
            }

            break;

        case 9:

            if(pNum==7){
                numContact=pNum;
            }

            break;

        case 10:
            
            if(pNum==13){
                numContact=pNum;
            }

            break;

        default:
            
            numContact=0;
            break;

    }

    return numContact;

}


static SDL_Rect mapTiles_getTile(int pNum, int pLine){
    
    static SDL_Rect rectTile;

    int nbCol=11;

    for(int i=0;i<nbCol;i++){

        int id=i+(nbCol*pLine);

        for(int n=0;n<3;n++){

            int numContact=mapTiles_getNumContact(i,pNum);

            if(numContact>0){
                rectTile.x=i*(TILESIZE*2);
                rectTile.y=pLine*TILESIZE;
                rectTile.w=TILESIZE*2;
                rectTile.h=TILESIZE;
                
                break;

            }


        }

    }

    return rectTile;

}



void mapTiles_draw(SDL_Renderer *pRenderer){

    /////////////MAP/////////////
    for(int l=0;l<MAP_HEIGHT;l++){
        
        for(int c=0;c<MAP_WIDTH;c++){
            
            int id=mapData[l][c];

            int x=(c-l)*(TILESIZE*scaleMap)+MAP_X;
            int y=(l+c)*((TILESIZE/2)*scaleMap)+MAP_Y;

            SDL_Rect dsRectTile={x,y,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap};
            SDL_Rect srRectTile;

            int numTile;

            if(id==0){
                
                srRectTile.x=1*(TILESIZE*2);
                srRectTile.y=3*TILESIZE;
                srRectTile.w=TILESIZE*2;
                srRectTile.h=TILESIZE;

                SDL_RenderCopy(pRenderer,mapImg,&srRectTile,&dsRectTile);
        
            }else if(id==1){
                
                numTile=mapTiles_getContact(l,c,id);
                srRectTile=mapTiles_getTile(numTile,1);

                SDL_RenderCopy(pRenderer,mapImg,&srRectTile,&dsRectTile);

            }else if(id==2){
                
                numTile=mapTiles_getContact(l,c,id);
                srRectTile=mapTiles_getTile(numTile,0);

                SDL_RenderCopy(pRenderer,mapImg,&srRectTile,&dsRectTile);

            }else if(id==3){
                
                numTile=mapTiles_getContact(l,c,id);
                srRectTile=mapTiles_getTile(numTile,2);

                SDL_RenderCopy(pRenderer,mapImg,&srRectTile,&dsRectTile);

            }

        }
    }

    ///////////ICON/////////////
    for(int n=0;n<nbIconTile;n++){

        if(lstIcon[n].bIsVisible){

            SDL_Texture *img;

            if(n<4){
                
                img=mapImgIcons;

            }else if(n==4){

                img=imgIcons;

            }else if(n==5){

                img=imgIconsIndex;

            }

            if(lstIcon[n].bIsActive){
                
                SDL_Rect dsRectIcon={lstIcon[n].xScreen-2,lstIcon[n].yScreen,TILESIZE*lstIcon[n].scale,TILESIZE*lstIcon[n].scale};
                SDL_RenderCopy(pRenderer,img,&lstIcon[n].rectActive,&dsRectIcon);
            
            }else{
                
                SDL_Rect dsRectIcon={lstIcon[n].xScreen,lstIcon[n].yScreen,TILESIZE*lstIcon[n].scale,TILESIZE*lstIcon[n].scale};
                SDL_RenderCopy(pRenderer,img,&lstIcon[n].rect,&dsRectIcon);

            }


        }
        
    }

}

void mapTiles_mousepressed(Uint8 pBtn, int pX,int pY){
    
    if(pBtn==1){
        
        bOnIcon=false;

        //////////////click icon///////////
        for(int n=0;n<nbIconTile;n++){
            
            bool bCollide=false;

            if(n<nbIconTile-1){

                bCollide=utils_checkCollision(pX,pY,1,1,lstIcon[n].xScreen,lstIcon[n].yScreen,
                                TILESIZE*2,TILESIZE*2);
            
            }else{

                bCollide=utils_checkCollision(pX,pY,1,1,lstIcon[n].xScreen,lstIcon[n].yScreen+TILESIZE,
                                TILESIZE*2,TILESIZE);

            }

            if(bCollide){
                
                if(!lstIcon[n].bIsActive && lstIcon[n].bIsVisible){
                    
                    mapBuildings_resetIconValue(true);
                    lstIcon[n].bIsActive=true;

                    for(int i=0;i<nbIconTile;i++){

                        if(i!=n){
                            lstIcon[i].bIsActive=false;
                            bOnIcon=true;
                        }
                    }   
            

                }

            }

        }

    
        ///////////////////////click tiles///////////
        if(currentTile!=-1){
      
            for(int l=0;l<MAP_HEIGHT;l++){
        
                for(int c=0;c<MAP_WIDTH;c++){

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
                    int id=mapData[line][column];

                    /////////collide with tile 3D iso////
                    bool bCollide=utils_checkCollision(pX,pY,1,1,x,y,(TILESIZE*2)*scaleMap,TILESIZE*scaleMap);
                    bool bCollideBuilding=mapTiles_collideBuilding(x,y);

                    if(id>=0 && bCollide && !bCollideBuilding  && !bOnIcon && bOnTile){
                   
                        mapData[line][column]=currentTile;
                        
                        return;

                    }
                    

                }
        
            }

        }

    }

}

void mapTiles_mousemoved(int pX,int pY){


}


void mapTiles_keypressed(SDL_Scancode pKey){

}

void mapTiles_mousewheel(int pY){

    ////scale +1
  /*  if(scaleMap<3 && pY<0){
        scaleMap+=0.5;

        return;

    }

    /////scale -1
    if(scaleMap>0.5 && pY>0){
        
        scaleMap-=0.5;

        return;

    }*/

}