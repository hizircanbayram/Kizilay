#include "Level.h"

void initLevel(Level level[], int size, ALLEGRO_BITMAP *image)
{
     for (int i = 0; i < size; ++i)
    {
        level[i].live = false;
        level[i].maxFrame = 25;
        level[i].curFrame = 0;
        level[i].frameCount = 0;
        level[i].frameDelay = 3;
        level[i].frameWidth = 750;
        level[i].frameHeight = 750;
        level[i].animationColumns = 5;
        level[i].animationDirection = 1;

        if (image != NULL)
            level[i].image = image;
    }
}



void drawLevel(Level level[], int size)
{
 	for(int i = 0; i < size; i++)
	{
		if(level[i].live)
		{
			int fx = (level[i].curFrame % level[i].animationColumns) * level[i].frameWidth;
			int fy = (level[i].curFrame / level[i].animationColumns) * level[i].frameHeight;

			al_draw_bitmap_region(level[i].image, fx, fy, level[i].frameWidth,
				level[i].frameHeight, level[i].x - level[i].frameWidth / 2, level[i].y - level[i].frameHeight / 2, 0);
		}
	}
}

void startLevel(Level level[], int size, int x, int y)
{
	for(int i = 0; i < size; i++)
	{
		if(!level[i].live)
		{
		    level[i].x = x;
			level[i].y = y;
			level[i].live = true;

			break;
        }
    }
}

void updateLevel(Level level[], int size)
{
 	for(int i = 0; i < size; i++)
	{
		if(level[i].live)
		{
			if(++level[i].frameCount >= level[i].frameDelay)
			{
				level[i].curFrame += level[i].animationDirection;
				if(level[i].curFrame >= level[i].maxFrame)
				{
					level[i].curFrame = 0;
					level[i].live = false;
				}

				level[i].frameCount = 0;
			}
		}
	}
}
