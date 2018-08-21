#ifndef LIGHTENING_H
#define LIGHTENING_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

#define boole int
#define true 1
#define false 0

#define NUM_BULLETS 5
#define NUM_MISSILES 1
#define NUM_ENEMIES 15
#define NUM_EXPLOSIONS 1

#include "SpaceShip.h"
#include "Explosion.h"
#include "Enemy.h"

typedef struct Lightening
{
    int ID;
    int x;
    int y;
    int live;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationRow;
    int animationColumns;
    int animationDirection;

    ALLEGRO_BITMAP *image;
}Lightening;


void initLightening(Lightening lights[], int size, ALLEGRO_BITMAP *image);
void fireLightening(Lightening lights[], int size, int *cntLight);
void updateLightening(Lightening lights[], int *i, int minimum);
void drawLightening(Lightening lights[], int size, int *i, boole *flagLight);
void collisionLightening(Enemies enemy[], int esize, Lightening lights[], int *cntLight, SpaceShip *ship, Explosion explosions[], int exp_size, boole *flagLight, int minimum);
int findMinimumLightening(Enemies enemy[], int esize);

#endif // LIGHTENING_H
