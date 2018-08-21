#ifndef LEVEL_H
#define LEVEL_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

typedef struct Level
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
}Level;


void initLevel(Level level[], int size, ALLEGRO_BITMAP *image);
void drawLevel(Level level[], int size);
void startLevel(Level level[], int size, int x, int y);
void updateLevel(Level level[], int size);

#endif // LEVEL_H
