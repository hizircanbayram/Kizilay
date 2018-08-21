#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

#define NUM_BULLETS 5
#define NUM_MISSILES 1
#define NUM_EXPLOSIONS 1

#define boole int
#define true 1
#define false 0

#include "Enemy.h"
#include "SpaceShip.h"
#include "Explosion.h"



typedef struct Lasers
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
}Lasers;


void initLasers(Lasers laser[], int size, ALLEGRO_BITMAP *image);
void fireLasers(Lasers laser[], int size, int *cntLaser);
void updateLasers(Lasers laser[], int *i);
void drawLasers(Lasers laser[], int size, int *i, boole *flagLaser);
void collisionLasers(Enemies enemy[], int esize, Lasers laser[], int *cntLaser, SpaceShip *ship, Explosion explosions[], int exp_size, boole *flagLaser);

#endif // LASER_H
