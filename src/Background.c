#include "Background.h"


void InitBackground(Background *back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
	back->x = x;
	back->y = y;
	back->velX = velx;
	back->velY = vely;
	back->width = width;
	back->height = height;
	back->dirX = dirX;
	back->dirY = dirY;
	back->image = image;
}
void UpdateBackground(Background *back)
{
	back->y += back->velY * back->dirY;
	if(back->y - back->height >= 0)
		back->y = 0;
}

void DrawBackground(Background *back)
{
	al_draw_bitmap(back->image, back->x, back->y, 0);

	if(back->y - back->height < 0)
		al_draw_bitmap(back->image, back->x, back->y - back->height, 0);
}
