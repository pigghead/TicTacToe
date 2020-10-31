// CircleHelper.cpp: This is a circle drawing helper class that utilizes Bresenham's circle drawing algorithm in computer science
//

#include "CircleHelper.h"

// drawCircle: Selects 8 points that are 45 degrees away from one another and draws a dot at each point
//
void CircleHelper::drawCircle(SDL_Renderer* ren, int xc, int yc, int x, int y) {
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);

	SDL_RenderDrawPoint(ren, xc + x, yc + y);
	SDL_RenderDrawPoint(ren, xc - x, yc + y);
	SDL_RenderDrawPoint(ren, xc + x, yc - y);
	SDL_RenderDrawPoint(ren, xc - x, yc - y);
						
	SDL_RenderDrawPoint(ren, xc + y, yc + x);
	SDL_RenderDrawPoint(ren, xc - y, yc + x);
	SDL_RenderDrawPoint(ren, xc + y, yc - x);
	SDL_RenderDrawPoint(ren, xc - y, yc - x);
}

// BresenhamCircleDraw: utilizes the drawCircle method in a loop to continuously draw the 8 points while shifting
//						the starting point
//
void CircleHelper::BresenhamCircleDraw(SDL_Renderer* ren, int xc, int yc, int r) {
	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(ren, xc, yc, x, y);
	while (y >= x) {
		// increment the value of x
		x++;

		// if d < 0, set d to 
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			y--;
			d = d + 4 * (x - y) + 10;
		}
		drawCircle(ren, xc, yc, x, y);
	}
}