#pragma once
#include <SDL.h>

class DrawBoard
{
public:
	void DrawGrid(SDL_Renderer* ren, unsigned int r, unsigned int g, unsigned int b);
	void ChangeGridColor(unsigned int rN, unsigned int rG, unsigned int rB);
	void UpdateBoard(SDL_Renderer* ren, int board[]);

private:
	const int N = 3;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int CELL_WIDTH = SCREEN_WIDTH / N;
	const int CELL_HEIGHT = SCREEN_HEIGHT / N;

	void DrawRows(SDL_Renderer* ren, unsigned int r, unsigned int g, unsigned int b);
	void DrawColumns(SDL_Renderer* ren, unsigned int r, unsigned int g, unsigned int b);
	void DrawX(SDL_Renderer* ren, int row, int column);
	void DrawO(SDL_Renderer* ren, int row, int column);


	struct RGB {
		unsigned int r = 0xC0;
		unsigned int g = 0xC0;
		unsigned int b = 0xC0;
	} GridRGB;

	enum GAME_STATE {
		RUNNING = 0,
		PLAYER_X_WON = 1,
		PLAYER_O_WON = 2,
		TIE = 3,
		QUIT = 4
	};

	enum BOARD_ENTRY {
		EMPTY = 0,
		PLAYER_X = 1, 
		PLAYER_O = 2
	};
};

