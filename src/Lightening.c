#include "Lightening.h"

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};

extern ALLEGRO_SAMPLE *light_skill;
extern ALLEGRO_SAMPLE *collision;
extern Enemies enemy[NUM_ENEMIES];
extern int killed_enemies;

void initLightening(Lightening lights[], int size, ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; ++i)
    {
        lights[i].ID = LIGHTENING;
        lights[i].live = 0;

        lights[i].maxFrame = 18;
        lights[i].curFrame = 0;
        lights[i].frameCount = 0;
        lights[i].frameDelay = 1;
        lights[i].frameWidth = 450; //degisecek
        lights[i].frameHeight = 450; //degisecek
        lights[i].animationColumns = 5; //degisecek
        lights[i].animationDirection = 1;

        lights[i].animationRow = 1; //degisecek
        lights[i].image = image;

        if (image != NULL)
            lights[i].image = image;
    }
}

void fireLightening(Lightening lights[], int size, int *cntLight)
{
    for (int i = 0; i < size; ++i)
    {
        lights[i].live = 1;
        lights[i].curFrame = 0;
    }

    *cntLight = -1;
}

void updateLightening(Lightening lights[], int *i, int minimum)
{
    if(lights[*i].live)
    {
        lights[*i].x = enemy[minimum].x;
        lights[*i].y = enemy[minimum].y;
        if(++lights[*i].frameCount >= lights[*i].frameDelay)
        {
            lights[*i].curFrame += lights[*i].animationDirection;
            if(lights[*i].curFrame >= lights[*i].maxFrame)
            {
                lights[*i].curFrame = 0;
                lights[*i].live = false;
            }

            lights[*i].frameCount = 0;
        }
    }
}

void collisionLightening(Enemies enemy[], int esize, Lightening lights[], int *cntLight, SpaceShip *ship, Explosion explosions[], int exp_size, boole *flagLight, int minimum)
{

    if ((enemy[minimum].y > 0) && (enemy[minimum].x > 0) && (enemy[minimum].live > 0))
    {
        startExplosions(explosions, exp_size, enemy[minimum].x, enemy[minimum].y);
        updateExplosions(explosions, NUM_EXPLOSIONS);
        drawExplosions(explosions, exp_size);
        ship->score += enemy[minimum].live;
        al_play_sample(light_skill, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        enemy[minimum].live = 0;
        ++killed_enemies;
        *flagLight = false;
    }
}

int findMinimumLightening(Enemies enemy[], int esize)
{
    int minimum;

    for (minimum = 0; minimum < esize; ++minimum)
        if (enemy[minimum].live > 0)
            break;

    for (int i = 0; i < esize; ++i)
    {

        if ((enemy[i].y > 0) && (enemy[i].x > 0) && (enemy[i].live > 0))
        {
            if (enemy[i].live < enemy[minimum].live)
            {
                minimum = i;
            }

        }
    }

    return minimum;
}



void drawLightening(Lightening lights[], int size, int *i, boole *flagLight)
{
		if(lights[*i].live)
		{
			int fx = (lights[*i].curFrame % lights[*i].animationColumns) * lights[*i].frameWidth;
			int fy = (lights[*i].curFrame / lights[*i].animationColumns) * lights[*i].frameHeight;

			al_draw_bitmap_region(lights[*i].image, fx, fy, lights[*i].frameWidth,
				lights[*i].frameHeight, lights[*i].x - lights[*i].frameWidth / 2, lights[*i].y - lights[*i].frameHeight / 2, 0);
		}
		else
		{
		    *flagLight == false;
		}
}
