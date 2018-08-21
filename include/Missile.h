#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//#include "Enemy.h"

#define NUM_BULLETS 5
#define NUM_MISSILES 1
#define WIDTH 750
#define HEIGHT 750

struct Enemies;
struct SpaceShip;

typedef struct Missile
{
	float x;
	float y;
	float velX;
	float velY;
	int live;
    int boundx;
    int boundy;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP *image;
}Missile;


void UpdateMissile(struct Enemies *enemy);
double AngleToTarget(double x1, double y1, double x2, double y2);
void collisionMissile(struct Enemies *enemy, int esize, int msize, struct SpaceShip *ship, ALLEGRO_BITMAP *e_image, int *state);
void InitMissile(struct Enemies *enemy2, ALLEGRO_BITMAP *m_image);
void AttractMissile(struct Enemies *enemy, int esize, int missilesize, struct SpaceShip *ship);
void DrawMissile(struct Enemies *enemy, int esize, int msize);

#endif // MISSILE_H
