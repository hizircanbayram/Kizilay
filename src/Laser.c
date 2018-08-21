#include "Laser.h"

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};

extern ALLEGRO_SAMPLE *laser_skill;
extern ALLEGRO_SAMPLE *collision ;
extern SpaceShip ship;
extern int killed_enemies;

void initLasers(Lasers laser[], int size, ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; ++i)
    {
        laser[i].ID = LASER;
        laser[i].live = 0;

        laser[i].maxFrame = 48;
        laser[i].curFrame = 0;
        laser[i].frameCount = 0;
        laser[i].frameDelay = 2;
        laser[i].frameWidth = 100;
        laser[i].frameHeight = 747;
        laser[i].animationColumns = 24;
        laser[i].animationDirection = 1;

        laser[i].animationRow = 2;
        laser[i].image = image;

        if (image != NULL)
            laser[i].image = image;
    }
}

void fireLasers(Lasers laser[], int size, int *cntLaser)
{
    for (int i = 0; i < size; ++i)
        laser[i].live = 1;

    *cntLaser = -1;
}

void updateLasers(Lasers laser[], int *i)
{
    if(laser[*i].live)
    {
        laser[*i].x = ship.x;
        laser[*i].y = ship.y - laser[*i].frameHeight / 2;
        if(++laser[*i].frameCount >= laser[*i].frameDelay)
        {
            laser[*i].curFrame += laser[*i].animationDirection;
            if(laser[*i].curFrame >= laser[*i].maxFrame)
            {
                laser[*i].curFrame = 0;
                laser[*i].live = false;
            }

            laser[*i].frameCount = 0;
        }
    }
}

void collisionLasers(Enemies enemy[], int esize, Lasers laser[], int *cntLaser, SpaceShip *ship, Explosion explosions[], int exp_size, boole *flagLaser)
{
    for (int i = 0; i < esize; ++i)
    {
        if (enemy[i].live && laser[*cntLaser].live && laser[*cntLaser].curFrame >= 26 && laser[*cntLaser].curFrame <= 34) //frameler 26-34
        {
            if ( (laser[*cntLaser].x - (laser[*cntLaser].frameWidth/2) < (enemy[i].x + enemy[i].boundx)) &&
                 (laser[*cntLaser].x + (laser[*cntLaser].frameWidth/2) > (enemy[i].x - enemy[i].boundx)) )
            {
                startExplosions(explosions, exp_size, enemy[i].x, enemy[i].y);
                updateExplosions(explosions, NUM_EXPLOSIONS);
                al_play_sample(laser_skill, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                drawExplosions(explosions, exp_size);
                ship->score += enemy[i].live;
                enemy[i].live = 0;
                ++killed_enemies;
            }
        }
    }
}

void drawLasers(Lasers laser[], int size, int *i, boole *flagLaser)
{
		if(laser[*i].live)
		{
			int fx = (laser[*i].curFrame % laser[*i].animationColumns) * laser[*i].frameWidth;
			int fy = (laser[*i].curFrame / laser[*i].animationColumns) * laser[*i].frameHeight;

			al_draw_bitmap_region(laser[*i].image, fx, fy, laser[*i].frameWidth,
				laser[*i].frameHeight, laser[*i].x - laser[*i].frameWidth / 2, laser[*i].y - laser[*i].frameHeight / 2, 0);
		}
		else
		{
		    *flagLaser == false;
		}
}
