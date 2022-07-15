#include "headers/mapBuildings.h"

#include "headers/mapTiles.h"
#include "headers/fireManager.h"

typedef struct Money Money; 
struct Money{

    int x;
    int y;

    int w;
    int h;

    float vx;
    float vy;

    float xScreen;
    float yScreen;

    float xTarget;
    float yTarget;

    int timerSpeed;
    int money;
    int idBuilding;

    bool bIsVisible;

};

typedef struct Losange Losange;
struct Losange
{

    int xScreen;
    int yScreen;

    float sizeImage;

    SDL_Point point[5];

    bool bIsValid;
};

typedef struct IconBuilding IconBuilding;
struct IconBuilding
{

    char type[255];
    char name[255];

    int x;
    int y;

    int xScreen;
    int yScreen;

    int w;
    int h;

    int scale;

    bool bIsActive;
    bool bIsVisible;

    int price;

    SDL_Texture *textPrice;
    SDL_Texture *textName;
};

typedef struct Building Building;
struct Building
{
    char name[255];
    char type[255];

    int x;
    int y;

    int oldX;
    int oldY;

    int w;
    int h;

    int xScreen;
    int yScreen;

    int id;

    bool bIsReverse;
    bool bIsMove;

    Losange losange;

    int price;
    int money;

    float timerSpeed;
    float timer;

    bool bOnBubble;
    SDL_Rect rectBubble;
};

static int nbExplore = 0;

static const int nbBuildingIcon = 17;
static const int ICON_SIZE = 32;

static const int HOME_SIZEW = 128;
static const int HOME_SIZEH = 116;

static const int BUILDING_SIZEW = 192;
static const int BUILDING_SIZEH = 136;

static const int BUILDING$_SIZEW = 128;
static const int BUILDING$_SIZEH = 86;

static int nbBuilding = 0;

static IconBuilding lstIconBuildings[17];
static Building lstBuildings[1000];

static Building *currentBuilding;
static Losange currentLosange;

static SDL_Texture *imgHomes;
static SDL_Texture *imgBuildings;
static SDL_Texture *imgBuildings_$;
static SDL_Texture *imgIcons;
static SDL_Texture *imgIconsIndex;

static SDL_Texture *imgBubble;
static SDL_Texture *imgMoney;

static Money lstMoney[500];
static int nbMoney=0;

static int buildingIdDelete;


static float mapBuildings_getPriceBuilding(char pName[])
{

    float price = 0;

    if (strcmp(pName, "HOME1") == 0)
    {

        price = 5000;
    }
    else if (strcmp(pName, "HOME2") == 0)
    {

        price = 10000;
    }
    else if (strcmp(pName, "HOME3") == 0)
    {

        price = 15000;
    }
    else if (strcmp(pName, "HOME4") == 0)
    {

        price = 25000;
    }
    else if (strcmp(pName, "POLICE") == 0)
    {

        price = 50000;
    }
    else if (strcmp(pName, "FIRE_STATION") == 0)
    {

        price = 70000;
    }
    else if (strcmp(pName, "HOSPITAL") == 0)
    {

        price = 90000;
    }
    else if (strcmp(pName, "PIZZERIA") == 0)
    {

        price = 30000;
    }
    else if (strcmp(pName, "MOVIE") == 0)
    {

        price = 55000;
    }
    else if (strcmp(pName, "BANK") == 0)
    {

        price = 60000;
    }

    return price;
}

void mapBuildings_init()
{
    buildingIdDelete=-1;

    for (int i = 0; i < nbBuildingIcon; i++)
    {

        lstIconBuildings[i].scale = 2;

        lstIconBuildings[i].x = 0;
        lstIconBuildings[i].y = 0;

        lstIconBuildings[i].xScreen = 0;
        lstIconBuildings[i].yScreen = gameplayService_screenHeight - (ICON_SIZE * lstIconBuildings[i].scale);

        lstIconBuildings[i].w = 0;
        lstIconBuildings[i].h = 0;

        lstIconBuildings[i].bIsVisible = true;
        lstIconBuildings[i].bIsActive = false;

        if (i > 2)
        {
            lstIconBuildings[i].bIsVisible = false;
        }

        switch (i)
        {

        /////////////ICON HOME
        case 0:

            lstIconBuildings[i].x = i * ICON_SIZE;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = ICON_SIZE;
            lstIconBuildings[i].h = ICON_SIZE;

            lstIconBuildings[i].xScreen = (ICON_SIZE * 4) - 14;

            strcpy(lstIconBuildings[i].type, "HOME_ICON");
            strcpy(lstIconBuildings[i].name, " ");

            break;

        ////////////ICON BUILDINGS
        case 1:

            lstIconBuildings[i].x = i * ICON_SIZE;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = ICON_SIZE;
            lstIconBuildings[i].h = ICON_SIZE;

            lstIconBuildings[i].xScreen = (ICON_SIZE * 6) - 14;

            strcpy(lstIconBuildings[i].type, "BUILDING_ICON");
            strcpy(lstIconBuildings[i].name, " ");

            break;

        ///////////ICON BUILDINGS $$
        case 2:

            lstIconBuildings[i].x = (i + 1) * ICON_SIZE;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = ICON_SIZE;
            lstIconBuildings[i].h = ICON_SIZE;

            lstIconBuildings[i].xScreen = (ICON_SIZE * 8) - 14;

            strcpy(lstIconBuildings[i].type, "BUILDING$_ICON");
            strcpy(lstIconBuildings[i].name, "");

            break;

        ///////////ICON CLOSE
        case 3:

            lstIconBuildings[i].x = (i - 3) * (ICON_SIZE - 11);
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = ICON_SIZE - 11;
            lstIconBuildings[i].h = ICON_SIZE - 11;

            lstIconBuildings[i].scale = 3;

            strcpy(lstIconBuildings[i].type, "CLOSE");
            strcpy(lstIconBuildings[i].name, " ");

            break;

        ////////////ICON VALID
        case 4:

            lstIconBuildings[i].x = (i - 3) * (ICON_SIZE - 11);
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].scale = 3;

            lstIconBuildings[i].w = ICON_SIZE - 11;
            lstIconBuildings[i].h = ICON_SIZE - 11;

            strcpy(lstIconBuildings[i].type, "VALID");
            strcpy(lstIconBuildings[i].name, "");

            break;

        ///////////ICON REVERSE
        case 5:

            lstIconBuildings[i].x = (i - 3) * (ICON_SIZE - 11);
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].scale = 3;

            lstIconBuildings[i].w = ICON_SIZE - 11;
            lstIconBuildings[i].h = ICON_SIZE - 11;

            strcpy(lstIconBuildings[i].type, "REVERSE");
            strcpy(lstIconBuildings[i].name, "");

            break;

        //////////////ICON HOME 1
        case 6:

            lstIconBuildings[i].x = 0 * HOME_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = HOME_SIZEW;
            lstIconBuildings[i].h = HOME_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (0 * (HOME_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (HOME_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "HOME1");
            strcpy(lstIconBuildings[i].type, "HOME");

            break;

        /////////////ICON HOME 2
        case 7:

            lstIconBuildings[i].x = 2 * HOME_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = HOME_SIZEW;
            lstIconBuildings[i].h = HOME_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (1 * (HOME_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (HOME_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "HOME2");
            strcpy(lstIconBuildings[i].type, "HOME");

            break;

        //////////ICON HOME 3
        case 8:

            lstIconBuildings[i].x = 4 * HOME_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].w = HOME_SIZEW;
            lstIconBuildings[i].h = HOME_SIZEH;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (2 * (HOME_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (HOME_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "HOME3");
            strcpy(lstIconBuildings[i].type, "HOME");

            break;

        /////////////ICON HOME 4
        case 9:
            lstIconBuildings[i].x = 6 * HOME_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = HOME_SIZEW;
            lstIconBuildings[i].h = HOME_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (3 * (HOME_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (HOME_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "HOME4");
            strcpy(lstIconBuildings[i].type, "HOME");

            break;

        ///////////ICON BUILDING 1
        case 10:
            lstIconBuildings[i].x = 0 * BUILDING_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = BUILDING_SIZEW;
            lstIconBuildings[i].h = BUILDING_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (0 * (BUILDING_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (BUILDING_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "FIRE_STATION");
            strcpy(lstIconBuildings[i].type, "BUILDING");

            break;

        ///////////ICON BUILDING 2
        case 11:
            lstIconBuildings[i].x = 2 * BUILDING_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].w = BUILDING_SIZEW;
            lstIconBuildings[i].h = BUILDING_SIZEH;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (1 * (BUILDING_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (BUILDING_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "POLICE");
            strcpy(lstIconBuildings[i].type, "BUILDING");

            break;

        ///////////////ICON BUILDING 3
        case 12:
            lstIconBuildings[i].x = 4 * BUILDING_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = BUILDING_SIZEW;
            lstIconBuildings[i].h = BUILDING_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (2 * (BUILDING_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (BUILDING_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "HOSPITAL");
            strcpy(lstIconBuildings[i].type, "BUILDING");

            break;

        ///////////ICON BUILDING $$$ 1
        case 13:
            lstIconBuildings[i].x = 0 * BUILDING$_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = BUILDING$_SIZEW;
            lstIconBuildings[i].h = BUILDING$_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (0 * (BUILDING$_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (BUILDING$_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "BANK");
            strcpy(lstIconBuildings[i].type, "BUILDING_$");

            break;

        ////////////ICON BUILDING $$$ 2
        case 14:
            lstIconBuildings[i].x = 2 * BUILDING$_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = BUILDING$_SIZEW;
            lstIconBuildings[i].h = BUILDING$_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (1 * (BUILDING$_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (BUILDING$_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "MOVIE");
            strcpy(lstIconBuildings[i].type, "BUILDING_$");

            break;

        /////////////ICON BUILDING $$$3
        case 15:
            lstIconBuildings[i].x = 4 * BUILDING$_SIZEW;
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = BUILDING$_SIZEW;
            lstIconBuildings[i].h = BUILDING$_SIZEH;

            lstIconBuildings[i].scale = 1;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth / 4 + (2 * (BUILDING$_SIZEW + 10));
            lstIconBuildings[i].yScreen = gameplayService_screenHeight - (BUILDING$_SIZEH * lstIconBuildings[i].scale) - 50;

            strcpy(lstIconBuildings[i].name, "PIZZERIA");
            strcpy(lstIconBuildings[i].type, "BUILDING_$");

            break;


         /////////////ICON DELETE
        case 16:
            lstIconBuildings[i].x = 3*(ICON_SIZE-11);
            lstIconBuildings[i].y = 0;

            lstIconBuildings[i].w = ICON_SIZE-11;
            lstIconBuildings[i].h = ICON_SIZE-11;

            lstIconBuildings[i].scale = 3;

            lstIconBuildings[i].xScreen = gameplayService_screenWidth-((ICON_SIZE-11)*3);
            lstIconBuildings[i].yScreen = gameplayService_screenHeight-(((ICON_SIZE-11)*3)*3);

            strcpy(lstIconBuildings[i].name, "");
            strcpy(lstIconBuildings[i].type, "DELETE");
        
            break;

        default:
            break;
        }

        lstIconBuildings[i].price =mapBuildings_getPriceBuilding(lstIconBuildings[i].name);

        TTF_Font *font = graphics_newFont("./font/Baby Doll.ttf", 20);
        lstIconBuildings[i].textName = graphics_newText(gameplayService_renderer, font, lstIconBuildings[i].name,
                                                        NULL);

        TTF_Font *fontPrice = graphics_newFont("./font/Baby Doll.ttf", 30);
        char charPrice[50];

        lstIconBuildings[i].textPrice =graphics_newText(gameplayService_renderer, fontPrice,
                                                            itoa(lstIconBuildings[i].price, charPrice, 10), NULL);
    }
}

void mapBuildings_setImages(SDL_Texture *pImgHomes, SDL_Texture *pImgBuildings, SDL_Texture *pImgBuildingsDollars, SDL_Texture *pImgIconsIndex, 
SDL_Texture *pImgIcons, SDL_Texture *pImgBubble,SDL_Texture *pImgMoney)
{

    imgHomes = pImgHomes;
    imgBuildings = pImgBuildings;
    imgBuildings_$ = pImgBuildingsDollars;
    imgIcons = pImgIcons;
    imgIconsIndex = pImgIconsIndex;

    imgBubble = pImgBubble;
    imgMoney=pImgMoney;
}

void mapBuildings_resetIconValue(bool pbIsIconTileActive)
{

    for (int i = 0; i < nbBuildingIcon; i++)
    {

        if(strcmp(lstIconBuildings[i].type,"DELETE")!=0){

            if (pbIsIconTileActive){

                lstIconBuildings[i].bIsVisible = false;
                lstIconBuildings[i].bIsActive = false;
            }
            else
            {

                if (i <= 2)
                {
                    lstIconBuildings[i].bIsVisible = true;
                    lstIconBuildings[i].bIsActive = false;
                }
            }

        }
    }
}

static void mapBuildings_reverseBuilding()
{

    ///////////////HOMES///////////////
    if (strcmp(currentBuilding->name, "HOME1") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 1 * HOME_SIZEW;
        }
        else
        {
            currentBuilding->x = 0 * HOME_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "HOME2") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 3 * HOME_SIZEW;
        }
        else
        {
            currentBuilding->x = 2 * HOME_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "HOME3") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 5 * HOME_SIZEW;
        }
        else
        {
            currentBuilding->x = 4 * HOME_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "HOME4") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 7 * HOME_SIZEW;
        }
        else
        {
            currentBuilding->x = 6 * HOME_SIZEW;
        }

        /////////////BUILDINGS
    }
    else if (strcmp(currentBuilding->name, "FIRE_STATION") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 1 * BUILDING_SIZEW;
        }
        else
        {
            currentBuilding->x = 0 * BUILDING_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "POLICE") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 3 * BUILDING_SIZEW;
        }
        else
        {
            currentBuilding->x = 2 * BUILDING_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "HOSPITAL") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 5 * BUILDING_SIZEW;
        }
        else
        {
            currentBuilding->x = 4 * BUILDING_SIZEW;
        }

        ////////////////BUILDING$/////////
    }
    else if (strcmp(currentBuilding->name, "BANK") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 1 * BUILDING$_SIZEW;
        }
        else
        {
            currentBuilding->x = 0 * BUILDING$_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "MOVIE") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 3 * BUILDING$_SIZEW;
        }
        else
        {
            currentBuilding->x = 2 * BUILDING$_SIZEW;
        }
    }
    else if (strcmp(currentBuilding->name, "PIZZERIA") == 0)
    {

        if (!currentBuilding->bIsReverse)
        {
            currentBuilding->x = 5 * BUILDING$_SIZEW;
        }
        else
        {
            currentBuilding->x = 4 * BUILDING$_SIZEW;
        }
    }

    if (!currentBuilding->bIsReverse)
    {
        currentBuilding->bIsReverse = true;
    }
    else
    {
        currentBuilding->bIsReverse = false;
    }
}

SDL_Rect mapBuildings_getRectBuilding(int pId, int pNum)
{

    if (pNum == 1)
    {

        SDL_Rect rect1 = {lstBuildings[pId].losange.xScreen - (TILESIZE * scaleMap), lstBuildings[pId].losange.yScreen + ((TILESIZE / 2) * scaleMap),
                        (TILESIZE * 2) * scaleMap, (TILESIZE * (lstBuildings[pId].losange.sizeImage - 1)) * scaleMap};

        return rect1;
    }
    else if (pNum == 2)
    {

        SDL_Rect rect2 = {lstBuildings[pId].losange.xScreen - ((TILESIZE * (lstBuildings[pId].losange.sizeImage - 1)) * scaleMap),
                        lstBuildings[pId].losange.yScreen + ((TILESIZE / 2) * (lstBuildings[pId].losange.sizeImage - 1) * scaleMap),
                        ((TILESIZE * 2) * (lstBuildings[pId].losange.sizeImage - 1)) * scaleMap, TILESIZE * scaleMap};

        return rect2;

    }
}

int mapBuildings_getNbBuilding()
{
    return nbBuilding;
}

static void mapBuildings_addBuilding(char pName[], char pType[])
{

    ////////////////HOMES//////////////
    if (strcmp(pType, "HOME") == 0)
    {

        lstBuildings[nbBuilding].w = HOME_SIZEW;
        lstBuildings[nbBuilding].h = HOME_SIZEH;

        strcpy(lstBuildings[nbBuilding].type, pType);

        lstBuildings[nbBuilding].timerSpeed = 60 * 2;

        if (strcmp(pName, "HOME1") == 0)
        {

            lstBuildings[nbBuilding].x = 0 * HOME_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "HOME2") == 0)
        {

            lstBuildings[nbBuilding].x = 2 * HOME_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "HOME3") == 0)
        {

            lstBuildings[nbBuilding].x = 4 * HOME_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "HOME4") == 0)
        {

            lstBuildings[nbBuilding].x = 6 * HOME_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }

        /////////////////////////BUILDING///////////
    }
    else if (strcmp(pType, "BUILDING") == 0)
    {

        lstBuildings[nbBuilding].w = BUILDING_SIZEW;
        lstBuildings[nbBuilding].h = BUILDING_SIZEH;

        strcpy(lstBuildings[nbBuilding].type, pType);

        lstBuildings[nbBuilding].timerSpeed = 60 * 3;

        if (strcmp(pName, "FIRE_STATION") == 0)
        {

            lstBuildings[nbBuilding].x = 0 * BUILDING_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "POLICE") == 0)
        {

            lstBuildings[nbBuilding].x = 2 * BUILDING_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "HOSPITAL") == 0)
        {

            lstBuildings[nbBuilding].x = 4 * BUILDING_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }

        ////////////////////BUILDING_$/////////////
    }
    else if (strcmp(pType, "BUILDING_$") == 0)
    {

        lstBuildings[nbBuilding].w = BUILDING$_SIZEW;
        lstBuildings[nbBuilding].h = BUILDING$_SIZEH;

        lstBuildings[nbBuilding].timerSpeed = 60;

        strcpy(lstBuildings[nbBuilding].type, pType);

        if (strcmp(pName, "BANK") == 0)
        {

            lstBuildings[nbBuilding].x = 0 * BUILDING$_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "MOVIE") == 0)
        {

            lstBuildings[nbBuilding].x = 2 * BUILDING$_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
        else if (strcmp(pName, "PIZZERIA") == 0)
        {

            lstBuildings[nbBuilding].x = 4 * BUILDING$_SIZEW;
            strcpy(lstBuildings[nbBuilding].name, pName);
        }
    }

    lstBuildings[nbBuilding].y = 0;

    lstBuildings[nbBuilding].price=mapBuildings_getPriceBuilding(pName);

    lstBuildings[nbBuilding].xScreen = MAP_X - ((lstBuildings[nbBuilding].w / 2) * scaleMap);
    lstBuildings[nbBuilding].yScreen = 0;

    lstBuildings[nbBuilding].bIsReverse = false;
    lstBuildings[nbBuilding].bIsMove = false;

    ////rect bubble
    lstBuildings[nbBuilding].rectBubble.x = lstBuildings[nbBuilding].xScreen + ((lstBuildings[nbBuilding].w / 4) * scaleMap);
    lstBuildings[nbBuilding].rectBubble.y = lstBuildings[nbBuilding].yScreen;
    lstBuildings[nbBuilding].rectBubble.w = TILESIZE * 2;
    lstBuildings[nbBuilding].rectBubble.h = TILESIZE * 2;

    lstBuildings[nbBuilding].bOnBubble = false;
    lstBuildings[nbBuilding].timer = lstBuildings[nbBuilding].timerSpeed;

    lstBuildings[nbBuilding].money = lstBuildings[nbBuilding].price / 1000;

    lstBuildings[nbBuilding].id = nbBuilding;

    currentBuilding = &lstBuildings[nbBuilding];

    /////////////////dimension image with the tiles////////////
    if (strcmp(pType, "BUILDING") == 0)
    {
        currentLosange.sizeImage = 3;
    }
    else
    {
        currentLosange.sizeImage = 2;
    }

    ///////////////losange select
    currentLosange.xScreen = lstBuildings[nbBuilding].xScreen + ((lstBuildings[nbBuilding].w / 2) * scaleMap);
    currentLosange.yScreen = lstBuildings[nbBuilding].yScreen + ((TILESIZE * 3) * scaleMap);

    currentLosange.point[0].x = currentLosange.xScreen;
    currentLosange.point[0].y = currentLosange.yScreen;

    currentLosange.point[1].x = currentLosange.xScreen + (((TILESIZE * 2) * (currentLosange.sizeImage / 2)) * scaleMap);
    currentLosange.point[1].y = currentLosange.yScreen + ((TILESIZE * (currentLosange.sizeImage / 2)) * scaleMap);

    currentLosange.point[2].x = currentLosange.xScreen;
    currentLosange.point[2].y = currentLosange.yScreen + ((TILESIZE * currentLosange.sizeImage) * scaleMap);

    currentLosange.point[3].x = currentLosange.xScreen - (((TILESIZE * 2) * (currentLosange.sizeImage / 2)) * scaleMap);
    currentLosange.point[3].y = currentLosange.yScreen + ((TILESIZE * (currentLosange.sizeImage / 2)) * scaleMap);

    currentLosange.point[4].x = currentLosange.xScreen;
    currentLosange.point[4].y = currentLosange.yScreen;

    currentLosange.bIsValid = true;

    nbBuilding += 1;
}

static void mapBuildings_addMoney(int pX,int pY,int pMoney,int pTimerSpeed,int pId){
   
    lstMoney[nbMoney].xScreen=(float)pX;
    lstMoney[nbMoney].yScreen=(float)pY;

    lstMoney[nbMoney].vx=0;
    lstMoney[nbMoney].vy=0;

    lstMoney[nbMoney].xTarget=(float)gameplayService_screenWidth-100;
    lstMoney[nbMoney].yTarget=5;

    lstMoney[nbMoney].timerSpeed=pTimerSpeed;
    lstMoney[nbMoney].money=pMoney;

    lstMoney[nbMoney].idBuilding=pId;
    lstMoney[nbMoney].bIsVisible=true;
   
    nbMoney+=1; 
}

static void mapBuildings_reloadLosangePos(int pX, int pY)
{

    ///////////calcul tuile 3D ISO position/////////
    float x = pX - (MAP_X + (TILESIZE * scaleMap));
    float y = pY - MAP_Y;

    float cTile = x / (TILESIZE * scaleMap);
    float lTile = y / ((TILESIZE / 2) * scaleMap);

    int line = abs((lTile - cTile) / 2);
    int column = abs((cTile + lTile) / 2);

    int xTile = (column - line) * (TILESIZE * scaleMap) + (MAP_X + (TILESIZE * scaleMap));
    int yTile = (line + column) * ((TILESIZE / 2) * scaleMap) + MAP_Y;

    currentLosange.xScreen = xTile;
    currentLosange.yScreen = yTile;

    currentLosange.point[0].x = currentLosange.xScreen;
    currentLosange.point[0].y = currentLosange.yScreen;

    currentLosange.point[1].x = currentLosange.xScreen + (((TILESIZE * 2) * (currentLosange.sizeImage / 2)) * scaleMap);
    currentLosange.point[1].y = currentLosange.yScreen + ((TILESIZE * (currentLosange.sizeImage / 2)) * scaleMap);

    currentLosange.point[2].x = currentLosange.xScreen;
    currentLosange.point[2].y = currentLosange.yScreen + ((TILESIZE * currentLosange.sizeImage) * scaleMap);

    currentLosange.point[3].x = currentLosange.xScreen - (((TILESIZE * 2) * (currentLosange.sizeImage / 2)) * scaleMap);
    currentLosange.point[3].y = currentLosange.yScreen + ((TILESIZE * (currentLosange.sizeImage / 2)) * scaleMap);

    currentLosange.point[4].x = currentLosange.xScreen;
    currentLosange.point[4].y = currentLosange.yScreen;

    ///////////////////////////valid losange ?////////////////////////////////

    currentLosange.bIsValid = true;

    SDL_Rect rectCollideLosange = {currentLosange.xScreen - (TILESIZE * scaleMap), currentLosange.yScreen + ((TILESIZE / 2) * scaleMap),
                                   (TILESIZE * 2) * scaleMap, (TILESIZE * (currentLosange.sizeImage - 1)) * scaleMap};

    SDL_Rect rectCollideLosange2 = {currentLosange.xScreen - ((TILESIZE * (currentLosange.sizeImage - 1)) * scaleMap),
                                    currentLosange.yScreen + ((TILESIZE / 2) * (currentLosange.sizeImage - 1) * scaleMap),
                                    ((TILESIZE * 2) * (currentLosange.sizeImage - 1)) * scaleMap,
                                    TILESIZE * scaleMap};

    ////////////collide with the buildings
    for (int n = nbBuilding; n > -1; n--)
    {

        if (currentBuilding->id != n)
        {

            ////rectangle vertical with the collide
            SDL_Rect rectCollideBuildingVertical = {lstBuildings[n].losange.xScreen - 5,
                                                    lstBuildings[n].losange.yScreen + 5, 10,
                                                    (TILESIZE * (lstBuildings[n].losange.sizeImage - 0.5)) * scaleMap};

            ////rectangle horizontal with the collide
            SDL_Rect rectCollideBuildingHorizontal = {
                lstBuildings[n].losange.xScreen - (((TILESIZE * 2) * lstBuildings[n].losange.sizeImage / 2) * scaleMap) + 10,
                lstBuildings[n].losange.yScreen + (TILESIZE * (lstBuildings[n].losange.sizeImage / 2) * scaleMap) - 5,
                ((TILESIZE * 2) * (lstBuildings[n].losange.sizeImage - 0.5)) * scaleMap, 10};

            bool bCollideVertical1 = utils_checkCollision(rectCollideLosange.x, rectCollideLosange.y, rectCollideLosange.w,
                                                          rectCollideLosange.h, rectCollideBuildingVertical.x, rectCollideBuildingVertical.y,
                                                          rectCollideBuildingVertical.w, rectCollideBuildingVertical.h);

            bool bCollideHorizontal1 = utils_checkCollision(rectCollideLosange.x, rectCollideLosange.y, rectCollideLosange.w,
                                                            rectCollideLosange.h, rectCollideBuildingHorizontal.x, rectCollideBuildingHorizontal.y,
                                                            rectCollideBuildingHorizontal.w, rectCollideBuildingHorizontal.h);

            bool bCollideVertical2 = utils_checkCollision(rectCollideLosange2.x, rectCollideLosange2.y, rectCollideLosange2.w,
                                                          rectCollideLosange2.h, rectCollideBuildingVertical.x, rectCollideBuildingVertical.y,
                                                          rectCollideBuildingVertical.w, rectCollideBuildingVertical.h);

            bool bCollideHorizontal2 = utils_checkCollision(rectCollideLosange2.x, rectCollideLosange2.y, rectCollideLosange2.w,
                                                            rectCollideLosange2.h, rectCollideBuildingHorizontal.x, rectCollideBuildingHorizontal.y,
                                                            rectCollideBuildingHorizontal.w, rectCollideBuildingHorizontal.h);

            if (bCollideVertical1 || bCollideHorizontal1 || bCollideVertical2 || bCollideHorizontal2)
            {
                currentLosange.bIsValid = false;
            }
        }
    }

    ////////////////collide with the tiles
    for (int l = 0; l < MAP_HEIGHT; l++)
    {

        for (int c = 0; c < MAP_WIDTH; c++)
        {

            int id = mapData[l][c];

            int x = (c - l) * (TILESIZE * scaleMap) + MAP_X;
            int y = (l + c) * ((TILESIZE / 2) * scaleMap) + MAP_Y;

            ////rectangle tile with the collide
            SDL_Rect rectCollideTile = {x + (((TILESIZE * 2) / 4) * scaleMap), y + (TILESIZE / 4) * scaleMap,
                                        ((TILESIZE * 2) / 3) * scaleMap, (TILESIZE / 3) * scaleMap};

            bool bCollideTile = utils_checkCollision(rectCollideLosange.x,
                                                     rectCollideLosange.y, rectCollideLosange.w, rectCollideLosange.h, rectCollideTile.x, rectCollideTile.y,
                                                     rectCollideTile.w, rectCollideTile.h);

            bool bCollideTile2 = utils_checkCollision(rectCollideLosange2.x,
                                                      rectCollideLosange2.y, rectCollideLosange2.w, rectCollideLosange2.h, rectCollideTile.x, rectCollideTile.y,
                                                      rectCollideTile.w, rectCollideTile.h);

            if ((bCollideTile || bCollideTile2) && id > 0)
            {
                currentLosange.bIsValid = false;
            }
        }
    }
}

void mapBuildings_delete(int pId){

    bool bIsDelete=false;

    for(int n=nbBuilding;n>-1;n--){
        
        if(n==pId){
            
            lstBuildings[n].bOnBubble=false;

            if(buildingIdDelete==n){
                buildingIdDelete=-1;

                lstIconBuildings[nbBuildingIcon-1].bIsActive=false;
                lstIconBuildings[nbBuildingIcon-1].bIsVisible=false;
            }

            lstBuildings[n]=lstBuildings[nbBuilding-1];
            lstBuildings[n].id=n;

            bIsDelete=true;
        }

    }

    if(bIsDelete){
        nbBuilding-=1;
    }

}

static void mapBuildings_moveBuilding()
{

    if (currentBuilding != NULL)
    {

        if (currentBuilding->bIsMove)
        {

            mapBuildings_reloadLosangePos(currentLosange.xScreen, currentLosange.yScreen);

            ////bubble
            currentBuilding->rectBubble.x = currentBuilding->xScreen + ((currentBuilding->w / 4) * scaleMap);
            currentBuilding->rectBubble.y = currentBuilding->yScreen;

            ///losange
            currentBuilding->xScreen = currentLosange.xScreen - ((currentBuilding->w / 2) * scaleMap);
            currentBuilding->yScreen = currentLosange.yScreen - ((TILESIZE * 3) * scaleMap);
        }
    }
}

static int mapBuildings_compare(const void *a, const void *b)
{

    Building const *building = a;
    Building const *otherBuilding = b;

    float z_order1 = building->losange.xScreen + building->losange.yScreen;
    float z_order2 = otherBuilding->losange.xScreen + otherBuilding->losange.yScreen;

    if (z_order1 > z_order2)
    {
        return -1;
    }else{
        return 1;
    }
    
}

static void mapBuildings_sortBuldingZ_order()
{

    /////////buildings Z Order
    for (int n = nbBuilding; n > -1; n--)
    {
        SDL_qsort(lstBuildings, nbBuilding, sizeof(lstBuildings[0]), mapBuildings_compare);
        
    }
}

void mapBuildings_update(float dt)
{

    mapBuildings_moveBuilding();

    /////////////ICONS///////////
    for (int i = 0; i < nbBuildingIcon; i++)
    {

        if (lstIconBuildings[i].bIsActive)
        {

            /////////////ICON HOME////////
            if (strcmp(lstIconBuildings[i].type, "HOME_ICON") == 0)
            {

                lstIconBuildings[i].bIsVisible = false;
                lstIconBuildings[i].bIsActive = false;

                lstIconBuildings[i + 1].bIsVisible = false;
                lstIconBuildings[i + 1].bIsActive = false;

                lstIconBuildings[i + 2].bIsVisible = false;
                lstIconBuildings[i + 2].bIsActive = false;

                ///////////icons home visible///////
                for (int n = 6; n <= 9; n++)
                {

                    lstIconBuildings[n].bIsVisible = true;
                    lstIconBuildings[n].bIsActive = false;
                }

                /////////icon close visible///
                lstIconBuildings[3].bIsVisible = true;
                lstIconBuildings[3].bIsActive = false;

                lstIconBuildings[3].xScreen = gameplayService_screenWidth - (gameplayService_screenWidth / 4);
                lstIconBuildings[3].yScreen = gameplayService_screenHeight - ((ICON_SIZE * lstIconBuildings[i].scale) * 2);

                //////////////ICON BUILDING////////
            }
            else if (strcmp(lstIconBuildings[i].type, "BUILDING_ICON") == 0)
            {

                lstIconBuildings[i].bIsVisible = false;
                lstIconBuildings[i].bIsActive = false;

                lstIconBuildings[i + 1].bIsVisible = false;
                lstIconBuildings[i + 1].bIsActive = false;

                lstIconBuildings[i - 1].bIsVisible = false;
                lstIconBuildings[i - 1].bIsActive = false;

                ///////////icons building visible///////
                for (int n = 10; n <= 12; n++)
                {

                    lstIconBuildings[n].bIsVisible = true;
                    lstIconBuildings[n].bIsActive = false;
                }

                /////////icon close visible///
                lstIconBuildings[3].bIsVisible = true;
                lstIconBuildings[3].bIsActive = false;

                lstIconBuildings[3].xScreen = gameplayService_screenWidth - (gameplayService_screenWidth / 4);
                lstIconBuildings[3].yScreen = gameplayService_screenHeight - ((ICON_SIZE * lstIconBuildings[i].scale) * 2);

                //////////////ICON BUILDING $////////////
            }
            else if (strcmp(lstIconBuildings[i].type, "BUILDING$_ICON") == 0)
            {

                lstIconBuildings[i].bIsVisible = false;
                lstIconBuildings[i].bIsActive = false;

                lstIconBuildings[i - 2].bIsVisible = false;
                lstIconBuildings[i - 2].bIsActive = false;

                lstIconBuildings[i - 1].bIsVisible = false;
                lstIconBuildings[i - 1].bIsActive = false;

                ///////////icons building$ visible///////
                for (int n = 13; n <= 15; n++)
                {

                    lstIconBuildings[n].bIsVisible = true;
                    lstIconBuildings[n].bIsActive = false;
                }

                /////////icon close visible///
                lstIconBuildings[3].bIsVisible = true;
                lstIconBuildings[3].bIsActive = false;

                lstIconBuildings[3].xScreen = gameplayService_screenWidth - (gameplayService_screenWidth / 4);
                lstIconBuildings[3].yScreen = gameplayService_screenHeight - ((ICON_SIZE * lstIconBuildings[i].scale) * 2);

                ///////////////////ICON CLOSE//////////////////
            }
            else if (strcmp(lstIconBuildings[i].type, "CLOSE") == 0)
            {

                for (int n = 2; n < 16; n++)
                {
                    lstIconBuildings[n].bIsVisible = false;
                    lstIconBuildings[n].bIsActive = false;
                }

                for (int n = 0; n < 3; n++)
                {
                    lstIconBuildings[n].bIsVisible = true;
                    lstIconBuildings[n].bIsActive = false;
                }

                if (currentBuilding != NULL)
                {
                    nbBuilding -= 1;
                    currentBuilding = NULL;
                }

                mapTiles_resetValueIcon(false);
            }
            else if (strcmp(lstIconBuildings[i].type, "VALID") == 0)
            {

                lstIconBuildings[i].bIsActive = false;

                ////losange valid?///
                if (currentBuilding != NULL)
                {

                    if (currentBuilding->price <= gameplayService_money)
                    {
                        currentBuilding->yScreen = (currentLosange.yScreen - (currentBuilding->h * scaleMap)) + ((TILESIZE * currentLosange.sizeImage) * scaleMap);
                        currentBuilding->losange = currentLosange;
                        currentBuilding->price = mapBuildings_getPriceBuilding(currentBuilding->name);

                        mapBuildings_sortBuldingZ_order();

                        gameplayService_money -= currentBuilding->price;
                    }
                    else
                    {
                        mapBuildings_delete(currentBuilding->id);
                    }

                    if (currentLosange.bIsValid)
                    {

                        for (int n = 0; n <= 5; n++)
                        {

                            if (n <= 2)
                            {
                                lstIconBuildings[n].bIsVisible = true;
                            }
                            else
                            {
                                lstIconBuildings[n].bIsVisible = false;
                            }

                            lstIconBuildings[n].bIsActive = false;
                        }
                    }

                    currentLosange;
                    currentBuilding = NULL;

                    mapTiles_resetValueIcon(false);
                }
            }
            else if (strcmp(lstIconBuildings[i].type, "REVERSE") == 0)
            {

                if (currentBuilding != NULL)
                {
                    mapBuildings_reverseBuilding();
                }

                lstIconBuildings[i].bIsActive = false;

            }else if(strcmp(lstIconBuildings[i].type, "DELETE") == 0){

                if(buildingIdDelete>-1){
                    mapBuildings_delete(buildingIdDelete);
                    buildingIdDelete=-1;
                }

                lstIconBuildings[i].bIsActive = false;
                lstIconBuildings[i].bIsVisible = false;
            }

            ////////////////buildings select/////////
            if (strcmp(lstIconBuildings[i].type, "HOME") == 0 || strcmp(lstIconBuildings[i].type, "BUILDING") == 0 ||
                strcmp(lstIconBuildings[i].type, "BUILDING_$") == 0)
            {

                mapBuildings_addBuilding(lstIconBuildings[i].name, lstIconBuildings[i].type);

                for (int n = 6; n < nbBuildingIcon; n++)
                {
                    lstIconBuildings[n].bIsVisible = false;
                    lstIconBuildings[n].bIsActive = false;
                }

                for (int n = 3; n <= 5; n++)
                {
                    lstIconBuildings[n].bIsVisible = true;
                    lstIconBuildings[n].bIsActive = false;

                    lstIconBuildings[n].xScreen = 50+ ((n-3) * ICON_SIZE * lstIconBuildings[n].scale);
                    lstIconBuildings[n].yScreen = gameplayService_screenHeight - (ICON_SIZE * lstIconBuildings[n].scale);
                }
            }
        }
    }

    ////buildings
    for (int n = nbBuilding; n > -1; n--)
    {

        if (!lstBuildings[n].bOnBubble && lstBuildings[n].timer>0)
        {

            if (currentBuilding == NULL || currentBuilding->id != lstBuildings[n].id)
            {
                lstBuildings[n].timer -= 0.1;

                if (lstBuildings[n].timer <= 0)
                {

                    lstBuildings[n].timer = 0;
                    lstBuildings[n].bOnBubble = true;

                    if(buildingIdDelete==n){

                        lstIconBuildings[nbBuildingIcon-1].bIsActive=false;
                        lstIconBuildings[nbBuildingIcon-1].bIsVisible=false;
                        buildingIdDelete=-1;

                    }
                    
                }
            }
        }
    }


    ////money animation
    if(nbMoney>0){

        for(int i=nbMoney;i>-1;i--){
            
            float angle=utils_angle(lstMoney[i].xScreen,lstMoney[i].yScreen,
            lstMoney[i].xTarget,lstMoney[i].yTarget);

            lstMoney[i].vx=10*60*cos((double)angle);
            lstMoney[i].vy=10*60*sin((double)angle);

            lstMoney[i].xScreen+=lstMoney[i].vx*dt;
            lstMoney[i].yScreen+=lstMoney[i].vy*dt;

            double distance=utils_dist((int)lstMoney[i].xScreen+TILESIZE,
            (int)lstMoney[i].yScreen,(int)lstMoney[i].xTarget,(int)lstMoney[i].yTarget);

            if(distance<3){
                
                gameplayService_money+=lstMoney[i].money;

                lstBuildings[lstMoney[i].idBuilding].timer=lstMoney[i].timerSpeed;
                lstMoney[i].bIsVisible=false;

                nbMoney-=1;
                bOnTile=true;

                break;
            }

        }

    }
}


static void mapBuildings_drawBubble(SDL_Renderer *pRenderer){
    
    for (int n = 0; n < nbBuilding; n++)
    {
        if(buildingIdDelete==n){

            SDL_Rect rectSrArrow={4*(TILESIZE-11),0,TILESIZE-11,TILESIZE-11};
            SDL_Rect rectDsArrow={lstBuildings[n].xScreen+(lstBuildings[n].w/2*scaleMap)-(TILESIZE-11),lstBuildings[n].yScreen-(TILESIZE),
            TILESIZE,TILESIZE};

            SDL_RenderCopy(pRenderer,imgIcons,&rectSrArrow,&rectDsArrow);
        }

           //////bubble money////
        if (lstBuildings[n].bOnBubble)
        {

            SDL_Rect rectSrBubble = {0, 0, TILESIZE, TILESIZE};
            SDL_Rect rectDsBubble = {lstBuildings[n].rectBubble.x, lstBuildings[n].rectBubble.y,
                                    lstBuildings[n].rectBubble.w * scaleMap, lstBuildings[n].rectBubble.h * scaleMap};

            SDL_RenderCopy(pRenderer, imgBubble, &rectSrBubble, &rectDsBubble);
        }

    }
}

void mapBuildings_draw(SDL_Renderer *pRenderer)
{

      /////////////losange select
    if (currentBuilding != NULL)
    {

        if (!currentLosange.bIsValid)
        {
            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        }

        SDL_RenderDrawLines(pRenderer, currentLosange.point, 5);
    }
    
    //////////////BUILDING//////////
    for (int n = 0; n < nbBuilding; n++)
    {
        SDL_Rect dsRect = {lstBuildings[n].xScreen,
                        lstBuildings[n].yScreen,
                        lstBuildings[n].w * scaleMap,
                        lstBuildings[n].h * scaleMap};

        SDL_Rect srRect = {lstBuildings[n].x, lstBuildings[n].y, lstBuildings[n].w, lstBuildings[n].h};

        SDL_Texture *img;
        if (strcmp(lstBuildings[n].type, "HOME") == 0)
        {
            img = imgHomes;
        }
        else if (strcmp(lstBuildings[n].type, "BUILDING") == 0)
        {
            img = imgBuildings;
        }
        else if (strcmp(lstBuildings[n].type, "BUILDING_$") == 0)
        {
            img = imgBuildings_$;
        }

        SDL_RenderCopy(pRenderer, img, &srRect, &dsRect);

    }

    mapBuildings_drawBubble(pRenderer);

    //////////////ICONS
    for (int i = 0; i < nbBuildingIcon; i++)
    {

        SDL_Rect dsRect = {lstIconBuildings[i].xScreen,
                           lstIconBuildings[i].yScreen,
                           lstIconBuildings[i].w * lstIconBuildings[i].scale,
                           lstIconBuildings[i].h * lstIconBuildings[i].scale};

        SDL_Rect srRect = {lstIconBuildings[i].x, lstIconBuildings[i].y, lstIconBuildings[i].w, lstIconBuildings[i].h};

        if (lstIconBuildings[i].bIsVisible)
        {

            ////rectangle icon
            if (strcmp(lstIconBuildings[i].type, "HOME") == 0 || strcmp(lstIconBuildings[i].type, "BUILDING") == 0 ||
                strcmp(lstIconBuildings[i].type, "BUILDING_$") == 0)
            {

                Uint8 colorRectangle[4] = {0, 0, 0, 100};

                /// rectangle
                graphics_rectangle(pRenderer, "fill", lstIconBuildings[i].xScreen,
                                   lstIconBuildings[i].yScreen,
                                   lstIconBuildings[i].w * lstIconBuildings[i].scale,
                                   (lstIconBuildings[i].h * lstIconBuildings[i].scale) + 50, colorRectangle);

                ////text
                graphics_drawText(pRenderer, lstIconBuildings[i].textName,
                                  lstIconBuildings[i].xScreen + ((lstIconBuildings[i].w / 4) * lstIconBuildings[i].scale),
                                  lstIconBuildings[i].yScreen + ((lstIconBuildings[i].h) * lstIconBuildings[i].scale));

                graphics_drawText(pRenderer, lstIconBuildings[i].textPrice, lstIconBuildings[i].xScreen + ((lstIconBuildings[i].w / 4) * lstIconBuildings[i].scale),
                                  lstIconBuildings[i].yScreen + ((lstIconBuildings[i].h + 20) * lstIconBuildings[i].scale));
            }

            ////////////ICON INDEX
            if (i < 3)
            {

                SDL_RenderCopy(pRenderer, imgIconsIndex, &srRect, &dsRect);

                /////////ICON
            }
            else if ((i >= 3 && i < 6 )|| i==16)
            {
             
                SDL_RenderCopy(pRenderer, imgIcons, &srRect, &dsRect);

                //////////HOME
            }
            else if (i >= 6 && i < 10)
            {

                SDL_RenderCopy(pRenderer, imgHomes, &srRect, &dsRect);

                //////////BUILDING
            }
            else if (i >= 10 && i < 13)
            {

                SDL_RenderCopy(pRenderer, imgBuildings, &srRect, &dsRect);

                ///////////BUILDING $$
            }
            else if (i >= 13 && i <= 15)
            {

                SDL_RenderCopy(pRenderer, imgBuildings_$, &srRect, &dsRect);
            }
        }
    }


    /////////Money
    if(nbMoney>0){
        
        for(int i=nbMoney;i>-1;i--){

            if(lstMoney[i].bIsVisible){
                
                SDL_Rect srRectMoney={0,0,TILESIZE,TILESIZE};
                SDL_Rect dsRectMoney={lstMoney[i].xScreen,lstMoney[i].yScreen,
            (TILESIZE*2)*scaleMap,(TILESIZE*2)*scaleMap};

                SDL_RenderCopy(pRenderer,imgMoney,&srRectMoney,&dsRectMoney);
            }

        }
    }
 
}

void mapBuildings_mousepressed(Uint8 pBtn, int pX, int pY)
{

    if (pBtn == 1)
    {

        ///////////icons
        for (int i = 0; i < nbBuildingIcon; i++)
        {

            bool bCollide = utils_checkCollision(pX, pY, 1, 1, lstIconBuildings[i].xScreen, lstIconBuildings[i].yScreen,
                                                 lstIconBuildings[i].w * lstIconBuildings[i].scale, lstIconBuildings[i].h * lstIconBuildings[i].scale);

            if (bCollide)
            {

                if (lstIconBuildings[i].bIsVisible && !lstIconBuildings[i].bIsActive)
                {
                    lstIconBuildings[i].bIsActive = true;

                    if(strcmp(lstIconBuildings[i].type,"DELETE")!=0){
                        buildingIdDelete=-1;
                        mapTiles_resetValueIcon(true);    
                    }

                    return;
                }
            }
        }

 
        if (currentBuilding == NULL)
        {

            for (int n = nbBuilding; n > -1; n--)
            {
                
                ////building delete
                bool bCollideBuilding= utils_checkCollision(pX, pY, 1, 1,
                    lstBuildings[n].xScreen,lstBuildings[n].yScreen,lstBuildings[n].w*scaleMap,
                    lstBuildings[n].h*scaleMap);

                int currentTile=mapTiles_getCurrentTile();
           
                if(bCollideBuilding && !lstBuildings[n].bOnBubble && currentTile==-1){

                    if(!lstIconBuildings[nbBuildingIcon-1].bIsVisible){
                        buildingIdDelete=n;
                        lstIconBuildings[nbBuildingIcon-1].bIsVisible=true;

                    }else{

                        if(buildingIdDelete==n){
                            buildingIdDelete=-1;
                            lstIconBuildings[nbBuildingIcon-1].bIsVisible=false;
                        }else{
                            buildingIdDelete=n;
                        }
                     
                    }

                    return;

                }
                
                ////bubble money
                if (lstBuildings[n].bOnBubble)
                {

                    bool bCollideBubble = utils_checkCollision(pX, pY, 1, 1,
                                                               lstBuildings[n].rectBubble.x, lstBuildings[n].rectBubble.y,
                                                               lstBuildings[n].rectBubble.w * scaleMap, lstBuildings[n].rectBubble.h * scaleMap);

                    if (bCollideBubble)
                    {
                        bOnTile=false;
                        mapBuildings_addMoney(lstBuildings[n].rectBubble.x,lstBuildings[n].rectBubble.y,
                        lstBuildings[n].money,lstBuildings[n].timerSpeed,n);

                        lstBuildings[n].bOnBubble = false;

                        return;
                    }


                }

            }
        }

        //////////current building////////
        if (currentBuilding != NULL)
        {

            bool bCollideBuilding = utils_checkCollision(currentBuilding->xScreen, currentBuilding->yScreen,
                                                         currentBuilding->w * scaleMap, currentBuilding->h * scaleMap, pX, pY, 1, 1);

            if (bCollideBuilding && !currentBuilding->bIsMove)
            {
                currentBuilding->bIsMove = true;
                return;
            }
            else
            {

                currentBuilding->bIsMove = false;
                return;
            }
        }
    }
}

void mapBuildings_keypressed(SDL_Scancode pKey)
{
}

void mapBuildings_mousewheel(int pY)
{

}

void mapBuildings_mousemoved(int pX, int pY)
{

    if (currentBuilding != NULL)
    {

        if (currentBuilding->bIsMove)
        {

            ///////////calcul tuile 3D ISO position/////////
            float xMouse = pX - (MAP_X + (TILESIZE * scaleMap));
            float yMouse = pY - MAP_Y;

            float cTile = xMouse / (TILESIZE * scaleMap);
            float lTile = yMouse / ((TILESIZE / 2) * scaleMap);

            int line = abs((lTile - cTile) / 2);
            int column = abs((cTile + lTile) / 2);

            int x = (column - line) * (TILESIZE * scaleMap) + (MAP_X + (TILESIZE * scaleMap));
            int y = (line + column) * ((TILESIZE / 2) * scaleMap) + MAP_Y;

            bool bCollideTile = utils_checkCollision(pX, pY, 1, 1, x, y, (TILESIZE * 2) * scaleMap, TILESIZE * scaleMap);

            int id = mapData[line][column];

            if (bCollideTile)
            {

                if (line >= 0 && column >= 0 && line <= MAP_HEIGHT - currentLosange.sizeImage && column <= MAP_WIDTH - currentLosange.sizeImage)
                {
                    currentLosange.xScreen = x;
                    currentLosange.yScreen = y;

                    if (id != 0)
                    {
                        currentLosange.bIsValid = false;
                    }
                    else
                    {
                        currentLosange.bIsValid = true;
                    }
                }
            }
        }
    }
}