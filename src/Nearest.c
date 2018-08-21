#include "Nearest.h"

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};

extern ALLEGRO_SAMPLE *near_skill;
extern ALLEGRO_SAMPLE *collision;
extern SpaceShip ship;
extern int killed_enemies;


void initNear(Nearest neary[], int size, ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; ++i)
    {
        neary[i].ID = NEAREST;
        neary[i].live = 0;

        neary[i].maxFrame = 18;
        neary[i].curFrame = 0;
        neary[i].frameCount = 0;
        neary[i].frameDelay = 1;
        neary[i].frameWidth = 680;
        neary[i].frameHeight = 680;
        neary[i].animationColumns = 6;
        neary[i].animationDirection = 1;

        neary[i].animationRow = 1;
        neary[i].image = image;

        if (image != NULL)
            neary[i].image = image;
    }
}

void fireNear(Nearest neary[], int size, int *cntNear)
{
    for (int i = 0; i < size; ++i)
    {
        neary[i].live = 1;
        neary[i].curFrame = 0;
    }


    *cntNear = -1;
}

void updateNear(Nearest neary[], int *i)
{
    if(neary[*i].live)
    {
        neary[*i].x = ship.x;
        neary[*i].y = ship.y;
        if(++neary[*i].frameCount >= neary[*i].frameDelay)
        {
            neary[*i].curFrame += neary[*i].animationDirection;
            if(neary[*i].curFrame >= neary[*i].maxFrame)
            {
                neary[*i].curFrame = 0;
                neary[*i].live = false;
            }

            neary[*i].frameCount = 0;
        }
    }
}

void drawNear(Nearest neary[], int size, int *i, boole *flagNear)
{
		if(neary[*i].live)
		{
			int fx = (neary[*i].curFrame % neary[*i].animationColumns) * neary[*i].frameWidth;
			int fy = (neary[*i].curFrame / neary[*i].animationColumns) * neary[*i].frameHeight;

			al_draw_bitmap_region(neary[*i].image, fx, fy, neary[*i].frameWidth,
				neary[*i].frameHeight, neary[*i].x - neary[*i].frameWidth / 2, neary[*i].y - neary[*i].frameHeight / 2, 0);
		}
}
void collisionNear(Enemies enemy[], int esize, Nearest neary[], int *cntNear, SpaceShip *ship, Explosion explosions[], int exp_size, boole *flagNear)
{
    int closest, distance, curDistance;

    for (closest = 0; closest < esize; ++closest)
        if (enemy[closest].live > 0)
            break;

    curDistance = ((ship->x - enemy[closest].x) * (ship->x - enemy[closest].x)) + ((ship->y - enemy[closest].y) * (ship->y - enemy[closest].y));

    for (int i = 0; i < esize; ++i)
    {
        if ((enemy[i].y > 0) && (enemy[i].x > 0) && (enemy[i].live > 0))
        {
            distance = ( (ship->x - enemy[i].x) * (ship->x - enemy[i].x) ) + ( (ship->y - enemy[i].y) * (ship->y - enemy[i].y) );

            if (distance < curDistance)
            {
                curDistance = distance;
                closest = i;
            }

        }
    }

    if ((enemy[closest].y > 0) && (enemy[closest].x > 0) && (enemy[closest].live > 0))
    {
        startExplosions(explosions, exp_size, enemy[closest].x, enemy[closest].y);
        updateExplosions(explosions, NUM_EXPLOSIONS);
        drawExplosions(explosions, exp_size);
        ship->score += enemy[closest].live;
        al_play_sample(near_skill, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        enemy[closest].live = 0;
        ++killed_enemies;
        *flagNear = false;
    }
}
