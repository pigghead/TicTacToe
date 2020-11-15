#include "DrawBoard.h"
#include "CircleHelper.h"

/* PRIVATE FUNCTIONS */

/* Drawing the rows to the screen
	@param ren: Renderer used for drawing to the screen
	@param r: red color
	@param b: blue color
	@param g: green color
*/
void DrawBoard::DrawRows(SDL_Renderer* ren, unsigned int r, unsigned int g, unsigned int b) {
	// Set color
	SDL_SetRenderDrawColor(ren, r, g, b, 0xFF);

	// Drawing the rows
	for (size_t i = 1; i < N; i++) {
		// (screen width / 3) * i
		int tempRow = (SCREEN_WIDTH / N) * i;
		SDL_RenderDrawLine(ren, tempRow, 0, tempRow, SCREEN_HEIGHT);
	}
}

/* Drawing the columns to the screen
	@param ren: Renderer used for drawing to the screen
	@param r: red color
	@param b: blue color
	@param g: green color
*/
void DrawBoard::DrawColumns(SDL_Renderer* ren, unsigned int r, unsigned int g, unsigned int b) {
	// Set color
	SDL_SetRenderDrawColor(ren, r, g, b, 0xFF);

	// Drawing the columns
	for (size_t i = 1; i < N; i++) {
		// (screen width / 3) * i
		int tempCol = (SCREEN_HEIGHT / N) * i;
		SDL_RenderDrawLine(ren, 0, tempCol, SCREEN_WIDTH, tempCol);
	}
}

/* Draw an X to the screen
	@param ren: Renderer used for drawing to the screen
	@param row: the targeted row
	@param column: the targeted column

*/
void DrawBoard::DrawX(SDL_Renderer* ren, int row, int column) {
	// Get the length of the side of a smaller square inside one of our cells
	const float halfBounds = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	// Center of the cell using centerX and centerY
	const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
	const float centerY = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

	SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);	// Red
	// Draws the top left to the bottom right
	SDL_RenderDrawLine(ren, centerX - halfBounds, centerY - halfBounds, centerX + halfBounds, centerY + halfBounds);
	SDL_RenderDrawLine(ren, centerX + halfBounds, centerY - halfBounds, centerX - halfBounds, centerY + halfBounds);
}

/* Draw an O to the screen using CircleHelper class
	@param ren: Renderer used for drawing to the screen
	@param row: the targeted row
	@param column: the targeted column

*/
void DrawBoard::DrawO(SDL_Renderer* ren, int row, int column) {
	// center of the outer cell/ square
	const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
	const float centerY = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);	// Blue
	CircleHelper::BresenhamCircleDraw(ren, centerX, centerY, 55);
}

/* PUBLIC FUNCTIONS */

/* Drawing the grid to the screen using the DrawRows and DrawColumns functions
	@param ren: Renderer used for drawing to the screen
	@param r: red color
	@param b: blue color
	@param g: green color
*/
void DrawBoard::DrawGrid(SDL_Renderer* ren, unsigned int r, unsigned int g, unsigned int b) {
	DrawRows(ren, r, g, b);
	DrawColumns(ren, r, g, b);
}

/* Change the color of the grid
	@param rN: the new red
	@param gN: the new green
	@param bN: the new blue
*/
void DrawBoard::ChangeGridColor(unsigned int rN, unsigned int gN, unsigned int bN) {
	GridRGB.r = rN;
	GridRGB.g = gN;
	GridRGB.b = bN;
}

void DrawBoard::UpdateBoard(SDL_Renderer* ren, int board[]) {
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			switch (board[i * 3 + j]) {
				case PLAYER_X:
					DrawX(ren, i, j);
					break;
				case PLAYER_O:
					DrawO(ren, i, j);
					break;
				default:
					break;
			}
		}
	}
}