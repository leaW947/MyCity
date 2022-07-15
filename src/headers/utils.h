#include <math.h>
#include <stdbool.h>
#include <time.h>

int utils_checkCollision(int pX1,int pY1,int pW1,int pH1,int pX2,int pY2,int pW2,int pH2);

double utils_dist(int pX1,int pY1,int pX2,int pY2);

float utils_angle(int pX1,int pY1,int pX2,int pY2);

float utils_random(int pMin,int pMax);