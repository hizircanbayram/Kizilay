#ifndef BULLET_H
#define BULLET_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

struct SpaceShip;

typedef struct Bullets
{
    int ID;
    int x;
    int y;
    bool live;
    int speed;
}Bullets;


void initBullets(Bullets bullet[], int size);
void fireBullets(Bullets bullet[], int size, struct SpaceShip *ship);
void updateBullets(Bullets bullet[], int size);
void drawBullets(Bullets bullet[], int size);

#endif // BULLET_H
