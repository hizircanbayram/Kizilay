#include "Bullet.h"
#include "SpaceShip.h"
#include <allegro5/allegro.h> //Main Allegro header

#include <allegro5/allegro_acodec.h>

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};

extern ALLEGRO_SAMPLE *shot;


void initBullets(Bullets bullet[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        bullet[i].ID = BULLET;
        bullet[i].speed = 10;
        bullet[i].live = false;
    }
}

void fireBullets(Bullets bullet[], int size, struct SpaceShip *ship)
{
    for (int i = 0; i < size; ++i)
    {
        if (!bullet[i].live)
        {
            bullet[i].x = ship->x;
            bullet[i].y = ship->y - 17;
            bullet[i].live = true;

            al_play_sample(shot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

            break;
        }
    }
}

void drawBullets(Bullets bullet[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (bullet[i].live)
        {
            al_draw_filled_circle(bullet[i].x, bullet[i].y, 3, al_map_rgb(173, 246, 13));
        }
    }
}

void updateBullets(Bullets bullet[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (bullet[i].live)
        {
            bullet[i].y -= bullet[i].speed;
            if (bullet[i].y < 0)
                bullet[i].live = false;
        }
    }
}
