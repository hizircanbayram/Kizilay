#include "SpaceShip.h"

enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};
enum KEYS {UP, DOWN, RIGHT, LEFT, SPACE, D, P, T};
extern bool keys[];

void initShip(SpaceShip *ship, ALLEGRO_BITMAP *image)
{
    ship->ID = PLAYER;
    ship->x = WIDTH/2;
    ship->y = HEIGHT - 70;
    ship->lives = 50;
    ship->speed = 6;
    ship->boundx = 33;
    ship->boundy = 33;
    ship->score = 0;

    ship->maxFrame = 3;
    ship->curFrame = 0;
    ship->frameCount = 0;
    ship->frameDelay = 50;
    ship->frameWidth = 82;
    ship->frameHeight = 82;
    ship->animationColumns = 1;
    ship->animationDirection = 1;

    ship->animationRow = 1;
    ship->image = image;

    if (image != NULL)
        ship->image = image;
}

void drawShip(SpaceShip *ship)
{

    int fy = (ship->curFrame % ship->animationColumns) * ship->frameWidth;
    int fx = ship->animationRow * ship->frameHeight;

   // al_draw_filled_rectangle(ship.x-ship.boundx, ship.y-ship.boundy, ship.x+ship.boundx, ship.y+ship.boundy, al_map_rgba(255, 0, 255, 100));

    al_draw_bitmap_region(ship->image, fx, fy, ship->frameWidth, ship->frameHeight,
                          ship->x - ship->frameWidth / 2, ship->y - ship->frameHeight / 2, 0);

}

void resetShipAnimation(SpaceShip *ship, int position)
{
    if (position == 1)
        ship->animationRow = 1;
    else
        ship->curFrame = 1;
}

void moveShipUp(SpaceShip *ship)
{
    ship->curFrame = 1;
    ship->y -= keys[UP] * ship->speed;
    if (ship->y < 0 + (ship->frameHeight - 40))
        ship->y = 0 + (ship->frameHeight - 40);
}

void moveShipDown(SpaceShip *ship)
{
    ship->curFrame = 0;
    ship->y += keys[DOWN] * ship->speed;
    if (ship->y > HEIGHT - (ship->frameHeight - 12))
        ship->y = HEIGHT - (ship->frameHeight - 12);
}

void moveShipRight(SpaceShip *ship)
{
    ship->animationRow = 2;
    ship->x += keys[RIGHT] * ship->speed;
    if (ship->x > WIDTH - (ship->frameWidth - 40))
        ship->x = WIDTH - (ship->frameWidth - 40);
}

void moveShipLeft(SpaceShip *ship)
{
    ship->animationRow = 0;
    ship->x -= keys[LEFT] * ship->speed;
    if (ship->x < 0 + (ship->frameWidth - 40))
        ship->x = 0 + (ship->frameWidth - 40);
}
