#include "Start.h"



void initStart(Start startup[], int size, ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; ++i)
    {
        startup[i].live = false;
        startup[i].maxFrame = 19;
        startup[i].curFrame = 0;
        startup[i].frameCount = 0;
        startup[i].frameDelay = 3;
        startup[i].frameWidth = 750;
        startup[i].frameHeight = 750;
        startup[i].animationColumns = 4;
        startup[i].animationDirection = 1;

        if (image != NULL)
            startup[i].image = image;
    }
}
void drawStart(Start startup[], int size)
{
 	for(int i = 0; i < size; i++)
	{
		if(startup[i].live)
		{
			int fx = (startup[i].curFrame % startup[i].animationColumns) * startup[i].frameWidth;
			int fy = (startup[i].curFrame / startup[i].animationColumns) * startup[i].frameHeight;

			al_draw_bitmap_region(startup[i].image, fx, fy, startup[i].frameWidth,
				startup[i].frameHeight, startup[i].x - startup[i].frameWidth / 2, startup[i].y - startup[i].frameHeight / 2, 0);
		}
	}
}
void updateStart(Start startup[], int size)
{
 	for(int i = 0; i < size; i++)
	{
		if(startup[i].live)
		{
            //printf("frame count : %d\n", startup[i].frameCount);
			if(++startup[i].frameCount >= startup[i].frameDelay)
			{
			    //printf("drawstart | curFrame : %d\n", startup[i].curFrame);
				startup[i].curFrame += startup[i].animationDirection;
				if(startup[i].curFrame >= startup[i].maxFrame)
				{
					startup[i].curFrame = 0;
					startup[i].live = false;
				}

				startup[i].frameCount = 0;
			}
		}
	}
}

void startStart(Start startup[], int size, int x, int y)
{
 	for(int i = 0; i < size; i++)
	{
		if(!startup[i].live)
		{
		    startup[i].x = x;
			startup[i].y = y;
			startup[i].live = true;

			break;
        }
    }
}
