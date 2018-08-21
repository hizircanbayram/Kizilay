#ifndef START_H
#define START_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

typedef struct Start
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
}Start;


void initStart(Start startup[], int size, ALLEGRO_BITMAP *image);
void startStart(Start startup[], int size, int x, int y);
void drawStart(Start startup[], int size);
void updateStart(Start startup[], int size);

#endif // START_H
