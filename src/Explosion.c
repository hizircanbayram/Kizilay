#include "Explosion.h"



enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};

void initExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; ++i)
    {
        explosions[i].live = false;
        explosions[i].maxFrame = 25;
        explosions[i].curFrame = 0;
        explosions[i].frameCount = 0;
        explosions[i].frameDelay = 1;
        explosions[i].frameWidth = 64;
        explosions[i].frameHeight = 64;
        explosions[i].animationColumns = 5;
        explosions[i].animationDirection = 1;

        if (image != NULL)
            explosions[i].image = image;
    }

}

void drawExplosions(Explosion explosions[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(explosions[i].live)
		{
			int fx = (explosions[i].curFrame % explosions[i].animationColumns) * explosions[i].frameWidth;
			int fy = (explosions[i].curFrame / explosions[i].animationColumns) * explosions[i].frameHeight;

			al_draw_bitmap_region(explosions[i].image, fx, fy, explosions[i].frameWidth,
				explosions[i].frameHeight, explosions[i].x - explosions[i].frameWidth / 2, explosions[i].y - explosions[i].frameHeight / 2, 0);
		}
	}
}

void startExplosions(Explosion explosions[], int size, int x, int y)
{
	for(int i = 0; i < size; i++)
	{
		if(!explosions[i].live)
		{
		    explosions[i].x = x;
			explosions[i].y = y;
			explosions[i].live = true;

			break;
        }
    }
}

void updateExplosions(Explosion explosions[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(explosions[i].live)
		{
			if(++explosions[i].frameCount >= explosions[i].frameDelay)
			{
				explosions[i].curFrame += explosions[i].animationDirection;
				if(explosions[i].curFrame >= explosions[i].maxFrame)
				{
					explosions[i].curFrame = 0;
					explosions[i].live = false;
				}

				explosions[i].frameCount = 0;
			}
		}
	}
}
