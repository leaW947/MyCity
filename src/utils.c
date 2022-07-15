#include "headers/utils.h"

int utils_checkCollision(int pX1,int pY1,int pW1,int pH1,int pX2,int pY2,int pW2,int pH2){

    if(pX1+pW1>=pX2 && pX1<=pX2+pW2){
        if(pY1+pH1>=pY2 && pY1<=pY2+pH2){

            return 1;
        }
    }

    return 0;

}

double utils_dist(int pX1,int pY1,int pX2,int pY2){

    return sqrt((pX2-pX1)^2+(pY2-pY2)^2);
}

float utils_angle(int pX1,int pY1,int pX2,int pY2){
    return atan2(pY2-pY1, pX2-pX1);
}

float utils_random(int pMin,int pMax){
    
    int maxNum=10;
    float numRand=rand()%maxNum;
    
    float num=numRand/maxNum;
    
    return (num*(pMax-pMin))+pMin;

}