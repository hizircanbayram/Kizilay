#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

#define WIDTH 750
#define HEIGHT 750

typedef struct SpaceShip
{
    int ID;
    int x;
    int y;
    int lives;
    int speed;
    int boundx;
    int boundy;
    int score;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    ALLEGRO_BITMAP *image;
}SpaceShip;


void initShip(SpaceShip *ship, ALLEGRO_BITMAP *image);
void resetShipAnimation(SpaceShip *ship, int position);
void drawShip(SpaceShip *ship);
void moveShipUp(SpaceShip *ship);
void moveShipDown(SpaceShip *ship);
void moveShipRight(SpaceShip *ship);
void moveShipLeft(SpaceShip *ship);

#endif // SPACESHIP_H
