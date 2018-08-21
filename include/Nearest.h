#ifndef NEAREST_H
#define NEAREST_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

#define boole int
#define true 1
#define false 0

#define NUM_EXPLOSIONS 1

#include "SpaceShip.h"
#include "Explosion.h"
#include "Enemy.h"


typedef struct Nearest
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
}Nearest;


void initNear(Nearest neary[], int size, ALLEGRO_BITMAP *image);
void fireNear(Nearest neary[], int size, int *cntNear);
void updateNear(Nearest neary[], int *i);
void drawNear(Nearest neary[], int size, int *i, boole *flagNear);
void collisionNear(Enemies enemy[], int esize, Nearest neary[], int *cntNear, SpaceShip *ship, Explosion explosions[], int exp_size, boole *flagNear);

#endif // NEAREST_H
