#include "Missile.h"
#include "Enemy.h"
#include "SpaceShip.h"

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};
enum STATE{TITLE, PLAYING, LOST, AUTOPILOT, SCORETABLE};

extern ALLEGRO_SAMPLE *bomb;
extern float gravity;

void InitMissile(Enemies *enemy2, ALLEGRO_BITMAP *m_image)
{
    for (int i = 0; i < NUM_MISSILES; ++i)
    {
        enemy2->e_missile[i].velX = 0.05;
        enemy2->e_missile[i].velY = 0.05;
        enemy2->e_missile[i].x = enemy2->x - enemy2->frameWidth/2;
        enemy2->e_missile[i].y = enemy2->y - enemy2->frameHeight/2;
        enemy2->e_missile[i].live = 1;
        enemy2->e_missile[i].boundx = 17;
        enemy2->e_missile[i].boundy = 17;

        enemy2->e_missile[i].maxFrame = 9;
        enemy2->e_missile[i].curFrame = 0;
        enemy2->e_missile[i].frameCount = 0;
        enemy2->e_missile[i].frameDelay = 5;
        enemy2->e_missile[i].frameWidth = 82;
        enemy2->e_missile[i].frameHeight = 82;
        enemy2->e_missile[i].animationColumns = 3;
        enemy2->e_missile[i].animationDirection = 1;
        //if (m_image != NULL)
            enemy2->e_missile[i].image = m_image;
    }
}

void UpdateMissile(Enemies *enemy)
{
    for (int i = 0; i < NUM_MISSILES; ++i)
    {
        if(++enemy->e_missile[i].frameCount >= enemy->e_missile[i].frameDelay)
        {
            enemy->e_missile[i].curFrame += enemy->e_missile[i].animationDirection;
            if(enemy->e_missile[i].curFrame >= enemy->e_missile[i].maxFrame)
                enemy->e_missile[i].curFrame = 0;
            else if(enemy->e_missile[i].curFrame <= 0)
                enemy->e_missile[i].curFrame = enemy->e_missile[i].maxFrame - 1;

           enemy->e_missile[i].frameCount = 0;
        }

        enemy->e_missile[i].x += enemy->e_missile[i].velX;
        enemy->e_missile[i].y += enemy->e_missile[i].velY;

        if((enemy->e_missile[i].x <= 0 - enemy->e_missile[i].frameWidth) ||
            (enemy->e_missile[i].x >= WIDTH + enemy->e_missile[i].frameWidth))
        {
            enemy->e_missile[i].live = 0;
        }
        else if((enemy->e_missile[i].y <= 0 - enemy->e_missile[i].boundy) ||
            (enemy->e_missile[i].y >= HEIGHT + enemy->e_missile[i].frameHeight))
        {
            enemy->e_missile[i].live = 0;
        }
    }
}


double AngleToTarget(double x1,double y1,double x2,double y2)
{
    double deltaX = (x2-x1);
    double deltaY = (y2-y1);

    return atan2(deltaY,deltaX);
}

void collisionMissile(Enemies enemy[], int esize, int msize, SpaceShip *ship, ALLEGRO_BITMAP *e_image, int *state)
{
    for (int i = 0; i < esize; ++i)
    {
        if (enemy[i].ID == ENEMY2)
        {
              for (int k = 0; k < msize; ++k)
              {
                    if (!enemy[i].e_missile[k].live && enemy[i].live)
                    {
                        InitMissile(&enemy[i], enemy[i].e_missile[k].image);
                    }

                    UpdateMissile(&enemy[i]);

                    if (enemy[i].e_missile[k].live && ship->lives > 0)
                    {
                        if ( ( (enemy[i].e_missile[k].x - enemy[i].e_missile[k].boundx) < (ship->x + ship->boundx) ) &&
                               ( (enemy[i].e_missile[k].x + enemy[i].e_missile[k].boundx) > (ship->x - ship->boundx) ) &&
                               ( (enemy[i].e_missile[k].y + enemy[i].e_missile[k].boundy) > (ship->y - ship->boundy) ) &&
                               ( (enemy[i].e_missile[k].y - enemy[i].e_missile[k].boundy) < (ship->y + ship->boundy) )    )

                        {
                            enemy[i].e_missile[k].live = 0;
                            al_play_sample(bomb, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                            ship->lives -= 2;
                            if (ship->lives <= 0)
                                ChangeState(state, LOST);
                        }
                    }
              }
        }
    }
}

void AttractMissile(Enemies enemy[], int esize, int missilesize, SpaceShip *ship)
{
    for (int k = 0; k < esize; ++k)
    {
        if (enemy[k].ID == ENEMY2)
        {
            for(int i = 0; i < missilesize; i++)
            {
                float dvx = 0;
                float dvy = 0;

                float angle = AngleToTarget(enemy[k].e_missile[i].x, enemy[k].e_missile[i].y, ship->x, ship->y);

                dvy += (gravity * sin(angle)) / 400;
                dvx += (gravity * cos(angle)) / 400;

                enemy[k].e_missile[i].velX += dvx;
                enemy[k].e_missile[i].velY += dvy;
            }
        }
    }

}

void DrawMissile(Enemies enemy[], int esize, int msize)
{
    for (int k = 0; k < esize; ++k)
    {
        if (enemy[k].ID == ENEMY2)
        {
            for (int i = 0; i < msize; ++i)
            {
                int fx = (enemy[k].e_missile[i].curFrame % enemy[k].e_missile[i].animationColumns) * enemy[k].e_missile[i].frameWidth;
                int fy = (enemy[k].e_missile[i].curFrame / enemy[k].e_missile[i].animationColumns) * enemy[k].e_missile[i].frameHeight;

                if (enemy[k].e_missile[i].live)
                {
                    //al_draw_filled_rectangle(enemy[k].e_missile[i].x-enemy[k].e_missile[i].boundx, enemy[k].e_missile[i].y-enemy[k].e_missile[i].boundy,
                      //                       enemy[k].e_missile[i].x+enemy[k].e_missile[i].boundx, enemy[k].e_missile[i].y+enemy[k].e_missile[i].boundy,
                        //                      al_map_rgba(255, 0, 255, 100));
                    al_draw_bitmap_region(enemy[k].e_missile[i].image, fx, fy, enemy[k].e_missile[i].frameWidth,
                                          enemy[k].e_missile[i].frameHeight, enemy[k].e_missile[i].x, enemy[k].e_missile[i].y, 0);
                }
            }
        }
    }
}
