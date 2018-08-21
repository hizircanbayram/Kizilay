#define WIDTH 750
#define HEIGHT 750
#define NUM_ENEMIES 15
#define NUM_MISSILES 1
#define NUM_BULLETS 5

#include "Enemy.h"

extern Enemies enemy0;
extern Enemies enemy1;
extern Enemies enemy2;
extern Enemies enemy3;
extern Enemies enemy4;
extern int killed_enemies;

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};

void initEnemy0(Enemies *enemy0, ALLEGRO_BITMAP *image)
{
        enemy0->ID = ENEMY0;
        enemy0->speed = 1;
        enemy0->live = 0;
        enemy0->boundx = 24;
        enemy0->boundy = 24;
        enemy0->e_bullets[0].ID = BULLET;

        for (int i = 0; i < NUM_BULLETS; ++i)
        {
            enemy0->e_bullets[i].live = false;
            enemy0->e_bullets[i].speed = 0;
        }

        enemy0->maxFrame = 9;
        enemy0->curFrame = 0;
        enemy0->frameCount = 0;
        enemy0->frameDelay = 3;
        enemy0->frameWidth = 55;
        enemy0->frameHeight = 55;
        enemy0->animationColumns = 3;
        enemy0->animationDirection = 1;

        if (image != NULL)
            enemy0->image = image;
}

void initEnemy1(Enemies *enemy1, ALLEGRO_BITMAP *image)
{
        enemy1->ID = ENEMY1;
        enemy1->speed = 1;
        enemy1->live = 0;
        enemy1->boundx = 38;
        enemy1->boundy = 25;
        enemy1->e_bullets[0].ID = BULLET;

        for (int i = 0; i < NUM_BULLETS; ++i)
        {
            enemy1->e_bullets[i].live = false;
            enemy1->e_bullets[i].speed = 8;
        }

        enemy1->maxFrame = 1;
        enemy1->curFrame = 0;
        enemy1->frameCount = 0;
        enemy1->frameDelay = 3;
        enemy1->frameWidth = 82;
        enemy1->frameHeight = 82;
        enemy1->animationColumns = 3;
        enemy1->animationDirection = 1;

        if (image != NULL)
            enemy1->image = image;
}

void initEnemy2(Enemies *enemy2, ALLEGRO_BITMAP *e_image, ALLEGRO_BITMAP *m_image)
{
        enemy2->ID = ENEMY2;
        enemy2->speed = 1;
        enemy2->live = 0;
        enemy2->boundx = 38;
        enemy2->boundy = 25;
        enemy2->e_bullets[0].ID = BULLET;

        for (int i = 0; i < NUM_BULLETS; ++i)
        {
            enemy2->e_bullets[i].live = false;
            enemy2->e_bullets[i].speed = 0;
        }

        enemy2->maxFrame = 9;
        enemy2->curFrame = 0;
        enemy2->frameCount = 0;
        enemy2->frameDelay = 3;
        enemy2->frameWidth = 82;
        enemy2->frameHeight = 82;
        enemy2->animationColumns = 3;
        enemy2->animationDirection = 1;
        if (e_image != NULL)
            enemy2->image = e_image;
}

void initEnemy3(Enemies *enemy3, ALLEGRO_BITMAP *image)
{
        enemy3->ID = ENEMY3;
        enemy3->speed = 3;
        enemy3->live = 0;
        enemy3->boundx = 38;
        enemy3->boundy = 25;
        enemy3->e_bullets[0].ID = BULLET;

        for (int i = 0; i < NUM_BULLETS; ++i)
        {
            enemy3->e_bullets[i].live = false;
            enemy3->e_bullets[i].speed = 7;
        }

        enemy3->maxFrame = 1;
        enemy3->curFrame = 0;
        enemy3->frameCount = 0;
        enemy3->frameDelay = 3;
        enemy3->frameWidth = 82;
        enemy3->frameHeight = 82;
        enemy3->animationColumns = 1;
        enemy3->animationDirection = 1;

        if (image != NULL)
            enemy3->image = image;
}

void initEnemy4(Enemies *enemy4, ALLEGRO_BITMAP *image)
{
        enemy4->ID = ENEMY4;
        enemy4->speed = 10;
        enemy4->live = 0;
        enemy4->boundx = 38;
        enemy4->boundy = 25;
        enemy4->e_bullets[0].ID = BULLET;

        for (int i = 0; i < NUM_BULLETS; ++i)
        {
            enemy4->e_bullets[i].live = false;
            enemy4->e_bullets[i].speed = 9;
        }

        enemy4->maxFrame = 1;
        enemy4->curFrame = 0;
        enemy4->frameCount = 0;
        enemy4->frameDelay = 1;
        enemy4->frameWidth = 82;
        enemy4->frameHeight = 82;
        enemy4->animationColumns = 1;
        enemy4->animationDirection = 1;

        if (image != NULL)
            enemy4->image = image;
}

void initEnemies(Enemies enemy[], Enemies *enemy0, Enemies *enemy1, Enemies *enemy2, Enemies *enemy3, Enemies *enemy4, SpaceShip *ship)
{
    if (killed_enemies < 10)
    {
        if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy0;
        if (!enemy[1].live && !enemy[1].e_bullets[0].live)      enemy[1] = *enemy0;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy0;
       /* if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy2;
        if (!enemy[1].live && !enemy[1].e_missile[0].live)      enemy[1] = *enemy2;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy2;*/
        if (!enemy[3].live && !enemy[3].e_bullets[0].live)      enemy[3] = *enemy0;
        if (!enemy[4].live && !enemy[4].e_bullets[0].live)      enemy[4] = *enemy0;
        if (!enemy[5].live && !enemy[5].e_bullets[0].live)      enemy[5] = *enemy0;
        if (!enemy[6].live && !enemy[6].e_bullets[0].live)      enemy[6] = *enemy0;
        if (!enemy[7].live && !enemy[7].e_bullets[0].live)      enemy[7] = *enemy0;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy0;
        if (!enemy[9].live && !enemy[9].e_bullets[0].live)      enemy[9] = *enemy0;
    }
    else if (killed_enemies >= 10 && killed_enemies < 25)
    {
        if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy1;
        if (!enemy[1].live && !enemy[1].e_bullets[0].live)      enemy[1] = *enemy1;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy1;
        if (!enemy[3].live && !enemy[3].e_bullets[0].live)      enemy[3] = *enemy1;
        if (!enemy[4].live && !enemy[4].e_bullets[0].live)      enemy[4] = *enemy1;
        if (!enemy[5].live && !enemy[5].e_bullets[0].live)      enemy[5] = *enemy1;
        if (!enemy[6].live && !enemy[6].e_bullets[0].live)      enemy[6] = *enemy1;
        if (!enemy[7].live && !enemy[7].e_bullets[0].live)      enemy[7] = *enemy1;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy1;
        if (!enemy[9].live && !enemy[9].e_bullets[0].live)      enemy[9] = *enemy1;
    }
    else if (killed_enemies >= 25 && killed_enemies < 40)
    {
        if (!enemy[0].live)                                     enemy[0] = *enemy0;
        if (!enemy[1].live && !enemy[1].e_bullets[0].live)      enemy[1] = *enemy3;
        if (!enemy[2].live)                                     enemy[2] = *enemy0;
        if (!enemy[3].live && !enemy[3].e_bullets[0].live)      enemy[3] = *enemy3;
        if (!enemy[4].live)                                     enemy[4] = *enemy0;
        if (!enemy[5].live && !enemy[5].e_bullets[0].live)      enemy[5] = *enemy3;
        if (!enemy[6].live)                                     enemy[6] = *enemy0;
        if (!enemy[7].live && !enemy[7].e_bullets[0].live)      enemy[7] = *enemy3;
        if (!enemy[8].live)                                     enemy[8] = *enemy0;
        if (!enemy[9].live && !enemy[9].e_bullets[0].live)      enemy[9] = *enemy3;
    }
   else if (killed_enemies >= 40 && killed_enemies < 55)
    {
        if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy3;
        if (!enemy[1].live && !enemy[1].e_bullets[0].live)      enemy[1] = *enemy3;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy1;
        if (!enemy[3].live && !enemy[3].e_bullets[0].live)      enemy[3] = *enemy3;
        if (!enemy[4].live && !enemy[4].e_bullets[0].live)      enemy[4] = *enemy3;
        if (!enemy[5].live && !enemy[5].e_bullets[0].live)      enemy[5] = *enemy1;
        if (!enemy[6].live && !enemy[6].e_bullets[0].live)      enemy[6] = *enemy3;
        if (!enemy[7].live && !enemy[7].e_bullets[0].live)      enemy[7] = *enemy3;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy1;
        if (!enemy[9].live && !enemy[9].e_bullets[0].live)      enemy[9] = *enemy3;
    }
    else if (killed_enemies >= 55 && killed_enemies < 70)
    {
        if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy1;
        if (!enemy[1].live && !enemy[1].e_bullets[0].live)      enemy[1] = *enemy3;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy1;
        if (!enemy[3].live && !enemy[3].e_bullets[0].live)      enemy[3] = *enemy3;
        if (!enemy[4].live && !enemy[4].e_missile[0].live)      enemy[4] = *enemy2;
        if (!enemy[5].live && !enemy[5].e_bullets[0].live)      enemy[5] = *enemy1;
        if (!enemy[6].live && !enemy[6].e_bullets[0].live)      enemy[6] = *enemy4;
        if (!enemy[7].live && !enemy[7].e_bullets[0].live)      enemy[7] = *enemy1;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy3;
        if (!enemy[9].live && !enemy[9].e_missile[0].live)      enemy[9] = *enemy2;
    }
    else if (killed_enemies >= 70 && killed_enemies < 90)
    {
        if (!enemy[0].live && !enemy[0].e_missile[0].live)      enemy[0] = *enemy2;
        if (!enemy[1].live && !enemy[1].e_bullets[0].live)      enemy[1] = *enemy3;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy4;
        if (!enemy[3].live && !enemy[3].e_missile[0].live)      enemy[3] = *enemy2;
        if (!enemy[4].live && !enemy[4].e_bullets[0].live)      enemy[4] = *enemy3;
        if (!enemy[5].live && !enemy[5].e_missile[0].live)      enemy[5] = *enemy2;
        if (!enemy[6].live && !enemy[6].e_missile[0].live)      enemy[6] = *enemy2;
        if (!enemy[7].live && !enemy[7].e_bullets[0].live)      enemy[7] = *enemy3;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy3;
        if (!enemy[9].live && !enemy[9].e_missile[0].live)      enemy[9] = *enemy2;
    }
    else if (killed_enemies >= 90 && killed_enemies < 120)
    {
        if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy3;
        if (!enemy[1].live && !enemy[1].e_missile[0].live)      enemy[1] = *enemy2;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy3;
        if (!enemy[3].live && !enemy[3].e_missile[0].live)      enemy[3] = *enemy2;
        if (!enemy[4].live && !enemy[4].e_bullets[0].live)      enemy[4] = *enemy3;
        if (!enemy[5].live && !enemy[5].e_missile[0].live)      enemy[5] = *enemy2;
        if (!enemy[6].live && !enemy[6].e_bullets[0].live)      enemy[6] = *enemy3;
        if (!enemy[7].live && !enemy[7].e_missile[0].live)      enemy[7] = *enemy2;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy4;
        if (!enemy[9].live && !enemy[9].e_missile[0].live)      enemy[9] = *enemy2;
    }
    else if (killed_enemies >= 120 && killed_enemies < 200)
    {
        if (!enemy[0].live && !enemy[0].e_bullets[0].live)      enemy[0] = *enemy2;
        if (!enemy[1].live && !enemy[1].e_missile[0].live)      enemy[1] = *enemy2;
        if (!enemy[2].live && !enemy[2].e_bullets[0].live)      enemy[2] = *enemy2;
        if (!enemy[3].live && !enemy[3].e_missile[0].live)      enemy[3] = *enemy2;
        if (!enemy[4].live && !enemy[4].e_bullets[0].live)      enemy[4] = *enemy2;
        if (!enemy[5].live && !enemy[5].e_missile[0].live)      enemy[5] = *enemy2;
        if (!enemy[6].live && !enemy[6].e_bullets[0].live)      enemy[6] = *enemy2;
        if (!enemy[7].live && !enemy[7].e_missile[0].live)      enemy[7] = *enemy2;
        if (!enemy[8].live && !enemy[8].e_bullets[0].live)      enemy[8] = *enemy4;
        if (!enemy[9].live && !enemy[9].e_missile[0].live)      enemy[9] = *enemy2;
    }
}


void startEnemies(Enemies enemy[], int size, ALLEGRO_FONT *font18, SpaceShip *ship)
{
    int x, y;
    int cnt = 0;

    for (int i = 0; i < size; ++i)
    {
        int random;
        if (killed_enemies < 10)
            random = rand() % 1200;
        else if (killed_enemies >= 10 && killed_enemies < 25)
            random = rand() % 1000;
        else if (killed_enemies >= 25 && killed_enemies < 40)
            random = rand() % 750;
        else if (killed_enemies >= 40 && killed_enemies < 55)
            random = rand() % 600;
        else if (killed_enemies >= 55 && killed_enemies < 70)
            random = rand() % 500;
        else if (killed_enemies >= 70 && killed_enemies < 90)
            random = rand() % 450;
        else if (killed_enemies >= 90 && killed_enemies < 120)
            random = rand() % 300;
        else if (killed_enemies >= 120 && killed_enemies < 200)
            random = rand() % 300;

        if (!enemy[i].live && !random)
        {
                 x = 30 + rand() % (WIDTH - 60);
                 y = -20;
                 for (int k = 0; k < size; ++k)
                 {
                     if (i != k)
                     {
                         if (enemy[k].live != 0)
                         {
                             if ( (x + enemy[i].boundx < enemy[k].x - enemy[k].boundx) ||
                                  (x - enemy[i].boundx > enemy[k].x + enemy[k].boundx) )
                             {
                                ++cnt;
                             }
                         }
                         else
                         {
                                ++cnt;
                         }

                     }
                 }

                if (cnt == NUM_ENEMIES-1)
                {
                    if (enemy[i].ID != ENEMY4)
                    {
                         enemy[i].x = x;
                         enemy[i].y = y;
                    }

                    if (enemy[i].ID == ENEMY0)
                        enemy[i].live = 1;
                    else if (enemy[i].ID == ENEMY1)
                        enemy[i].live = 2;
                    else if (enemy[i].ID == ENEMY2)
                        enemy[i].live = 3;
                    else if (enemy[i].ID == ENEMY3)
                        enemy[i].live = 1;
                    else if (enemy[i].ID == ENEMY4)
                        enemy[i].live = 1;
                }
                if (enemy[i].ID == ENEMY4)
                {
                    enemy[i].x = ship->x;
                    enemy[i].y = -10;
                    enemy[i].live = 2;

                }
        }
        if (!enemy[i].e_bullets[0].live && enemy[i].live && enemy[i].ID != ENEMY0 && enemy[i].ID != ENEMY2)
        {
            enemy[i].e_bullets[0].x = enemy[i].x;
            enemy[i].e_bullets[0].y = enemy[i].y + 17;
            enemy[i].e_bullets[0].live = true;
        }
    }
}

void updateEnemies(Enemies enemy[], int size, ALLEGRO_FONT *font18, SpaceShip *ship)
{

	for(int i = 0; i < size; i++)
	{
		if(enemy[i].live)
		{
            if (enemy[i].ID == ENEMY0)
            {
                if (enemy[i].y > 55)
                    enemy[i].y = 55;

                enemy[i].y += enemy[i].speed;
            }

            else if (enemy[i].ID == ENEMY1)
            {
                if (enemy[i].y > 55)
                    enemy[i].y = 55;

                enemy[i].y += enemy[i].speed;
            }

            else if (enemy[i].ID == ENEMY2)
            {
                if (enemy[i].y > 55)
                    enemy[i].y = 55;

                enemy[i].y += enemy[i].speed;
            }

            else if (enemy[i].ID == ENEMY3)
            {
                enemy[i].y += enemy[i].speed;
            }

            else if (enemy[i].ID == ENEMY4)
            {
                if (enemy[i].y > 120)
                     enemy[i].y = 120;

                enemy[i].y += enemy[i].speed / 2;

                if (ship->x - enemy[i].x > 0)
                    enemy[i].x += enemy[i].speed / ship->speed * 2;
                else if (ship->x - enemy[i].x == 0)
                    ;
                else
                    enemy[i].x -= enemy[i].speed / ship->speed * 2;
            }

			if(++enemy[i].frameCount >= enemy[i].frameDelay)
			{
				enemy[i].curFrame += enemy[i].animationDirection;
				if(enemy[i].curFrame >= enemy[i].maxFrame)
				{
					enemy[i].curFrame = 0;
				}

				enemy[i].frameCount = 0;
			}
		}

		if (enemy[i].e_bullets[0].live)
        {
            enemy[i].e_bullets[0].y += enemy[i].e_bullets[0].speed;
            if (enemy[i].e_bullets[0].y > HEIGHT)
            {
                    enemy[i].e_bullets[0].live = false;
            }
        }
	}
}


void drawEnemies(Enemies enemy[], int size, ALLEGRO_FONT *font18)
{
    for (int i = 0; i < size; ++i)
    {
        if (enemy[i].live)
        {
             int fx = (enemy[i].curFrame % enemy[i].animationColumns) * enemy[i].frameWidth;
             int fy = (enemy[i].curFrame / enemy[i].animationColumns) * enemy[i].frameHeight;

             al_draw_bitmap_region(enemy[i].image, fx, fy, enemy[i].frameWidth,
                                   enemy[i].frameHeight, enemy[i].x - enemy[i].frameWidth/2, enemy[i].y - enemy[i].frameHeight/2, 0);

           // al_draw_filled_rectangle(enemy[i].x - enemy[i].boundx, enemy[i].y - enemy[i].boundy,
             //                       enemy[i].x + enemy[i].boundx, enemy[i].y + enemy[i].boundy, al_map_rgb(255, 0, 255));
        }
       if (enemy[i].e_bullets[0].live)
       {
            al_draw_filled_circle(enemy[i].e_bullets[0].x, enemy[i].e_bullets[0].y, 3, al_map_rgb(254, 253, 1));
       }
    }
}
