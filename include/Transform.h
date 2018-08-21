#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

typedef struct Transform
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
}Transform;


void initTransform(Transform tr_ship[], int size, ALLEGRO_BITMAP *image);
void drawTransform(Transform tr_ship[], int size);
void startTransform(Transform tr_ship[], int size, int x, int y);
void updateTransform(Transform tr_ship[], int size);

#endif // TRANSFORM_H
