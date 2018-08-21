#include "Transform.h"

void initTransform(Transform tr_ship[], int size, ALLEGRO_BITMAP *image)
{
    for (int i = 0; i < size; ++i)
    {
        tr_ship[i].live = false;
        tr_ship[i].maxFrame = 24;
        tr_ship[i].curFrame = 0;
        tr_ship[i].frameCount = 0;
        tr_ship[i].frameDelay = 1;
        tr_ship[i].frameWidth = 164;
        tr_ship[i].frameHeight = 164;
        tr_ship[i].animationColumns = 8;
        tr_ship[i].animationDirection = 1;

        if (image != NULL)
            tr_ship[i].image = image;
    }
}

void drawTransform(Transform tr_ship[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(tr_ship[i].live)
		{
			int fx = (tr_ship[i].curFrame % tr_ship[i].animationColumns) * tr_ship[i].frameWidth;
			int fy = (tr_ship[i].curFrame / tr_ship[i].animationColumns) * tr_ship[i].frameHeight;

			al_draw_bitmap_region(tr_ship[i].image, fx, fy, tr_ship[i].frameWidth,
				tr_ship[i].frameHeight, tr_ship[i].x - tr_ship[i].frameWidth / 2, tr_ship[i].y - tr_ship[i].frameHeight / 2, 0);
		}
	}
}

void startTransform(Transform tr_ship[], int size, int x, int y)
{
	for(int i = 0; i < size; i++)
	{
		if(!tr_ship[i].live)
		{
		    tr_ship[i].x = x;
			tr_ship[i].y = y;
			tr_ship[i].live = true;

			break;
        }
    }
}

void updateTransform(Transform tr_ship[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(tr_ship[i].live)
		{
			if(++tr_ship[i].frameCount >= tr_ship[i].frameDelay)
			{
				tr_ship[i].curFrame += tr_ship[i].animationDirection;
				if(tr_ship[i].curFrame >= tr_ship[i].maxFrame)
				{
					tr_ship[i].curFrame = 0;
					tr_ship[i].live = false;
				}

				tr_ship[i].frameCount = 0;
			}
		}
	}
}
