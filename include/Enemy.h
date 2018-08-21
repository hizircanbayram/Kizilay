#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



#include "SpaceShip.h"
#include "Bullet.h"
#include "Missile.h"



typedef struct Enemies
{
    int ID;
    int x;
    int y;
    int speed;
    int boundx;
    int boundy;
    int live;
    Bullets e_bullets[NUM_BULLETS];
    Missile e_missile[NUM_MISSILES];

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    ALLEGRO_BITMAP *image;

}Enemies;


void initEnemy0(Enemies *enemy0, ALLEGRO_BITMAP *image);
void initEnemy1(Enemies *enemy1, ALLEGRO_BITMAP *image);
void initEnemy2(Enemies *enemy2, ALLEGRO_BITMAP *e_image, ALLEGRO_BITMAP *m_image);
void initEnemy3(Enemies *enemy3, ALLEGRO_BITMAP *image);
void initEnemy4(Enemies *enemy4, ALLEGRO_BITMAP *image);

void initEnemies(Enemies enemy[], Enemies *enemy0, Enemies *enemy1, Enemies *enemy2, Enemies *enemy3, Enemies *enemy4, SpaceShip *ship);
void startEnemies(Enemies enemy[], int size, ALLEGRO_FONT *font18, SpaceShip *ship);
void updateEnemies(Enemies enemy[], int size, ALLEGRO_FONT *font18, SpaceShip *ship);
void drawEnemies(Enemies enemy[], int size, ALLEGRO_FONT *font18);

#endif // ENEMY_H
