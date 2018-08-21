#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>


typedef struct Explosion
{
    int x;
    int y;
    bool live;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    ALLEGRO_BITMAP *image;
}Explosion;


void initExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *image);
void drawExplosions(Explosion explosions[], int size);
void startExplosions(Explosion explosions[], int size, int x, int y);
void updateExplosions(Explosion explosions[], int size);

#endif // EXPLOSION_H
