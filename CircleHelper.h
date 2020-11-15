#pragma once
#include <SDL.h>

class CircleHelper
{
public:
	static void BresenhamCircleDraw(SDL_Renderer* ren, int xc, int yc, int r);
private:
	static void drawCircle(SDL_Renderer* ren, int xc, int yc, int x, int y);
};

