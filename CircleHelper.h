#pragma once
#include <SDL.h>

class CircleHelper
{
public:
	void BresenhamCircleDraw(SDL_Renderer* ren, int xc, int yc, int r);
private:
	void drawCircle(SDL_Renderer* ren, int xc, int yc, int x, int y);
};

