// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>

// SDL2 includes
#include <SDL.h>
#include <SDL_image.h>

#include "CircleHelper.h"
#include "DrawBoard.h"
#include "Game.h"

#undef main

/* Global Constants */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// size of each cell
const int CELL_WIDTH = SCREEN_WIDTH / 3;
const int CELL_HEIGHT = SCREEN_HEIGHT / 3;

static CircleHelper c;
static DrawBoard db;

unsigned int r = 0xC0;
unsigned int g = 0xC0;
unsigned int b = 0xC0;

std::string board[3][3] = { {"1","2","3"}, 
							{"4","5","6"}, 
							{"7","8","9"} 
};

/* CONSOLE IMPLEMENTATION */
// Print the board and its current layout
void PrintBoard();
// Check if there is a row of three
bool CheckWin();
// Reset the board
void Restart();
// Check valid player input
bool CheckValidInput(std::string input);

/* SDL2 IMPLEMENTATION */
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Enumeration for game state
enum GAME_STATE {
	RUNNING_STATE = 0,
	PLAYER_X_WINS = 1,
	PLAYER_O_WINS = 2,
	TIE = 3,
	QUIT = 4
};

// Enumeration for board entry
enum BOARD_ENTRY {
	EMPTY = 0,
	PLAYER_X = 1,
	PLAYER_O = 2
};

// Initialize game board to be empty
int guiBoard[9] = { 
	EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY 
};

int currentPlayer = PLAYER_X;

int currentBoardState = RUNNING_STATE;

void DrawGrid();  // draws the lines
void CellClicked(int cellWidth, int cellHeight);
void ChangePlayerTurn();
void DrawX(int row, int column);
//void DrawO(int row, int column);
void DrawwBoard();  // this differs from draw grid in that it will update the spaces when a player plays the space
int GuiCheckWin(int currPlayer);
void GuiReportWinningPlayer(int currPlayer);
void ResetGame();

bool quit = false;

int main() {
	// Lazy initialization bc we know little errors will happen
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("Tic Tac Toe", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	gRenderer = SDL_CreateRenderer(gWindow, 0, NULL);

	// Quit flag
	bool quit = false;

	while (currentBoardState != QUIT) {
		// Event checking
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					currentBoardState = QUIT;
					break;
				case SDL_MOUSEBUTTONDOWN:  // Check win, if no win then proceed
					CellClicked(e.button.y / CELL_HEIGHT, e.button.x / CELL_WIDTH);
					if (GuiCheckWin(currentPlayer) == 1) {
						GuiReportWinningPlayer(currentPlayer);
					}
					else {
						ChangePlayerTurn();
					}
					break;
				default:
					break;
			}
		}

		// Set render draw color
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);

		SDL_RenderClear(gRenderer);

		db.DrawGrid(gRenderer, r, g, b);
		db.UpdateBoard(gRenderer, guiBoard);

		SDL_RenderPresent(gRenderer);

	}

	/* CONSOLE/ DEBUG WINDOW IMPLEMNTATION
	PrintBoard();

	std::string p1;
	std::string p2;

	std::cout << "Enter player 1's name (X): ";
	std::cin >> p1;

	std::cout << "Enter player 2's name (O): ";
	std::cin >> p2;

	while (!quit) {
		// Player 1 logic
		std::string p1Space;
		std::cout << "P1 select a space: ";

		// Check for valid input on p1 response
		do {
			std::cin >> p1Space;
		} while (!CheckValidInput(p1Space));
		
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (board[i][j] == p1Space && (board[i][j] != "X" || board[i][j] != "O"))
				{
					board[i][j] = "X";
					break;
				}
			}
		}

		PrintBoard();
		if (CheckWin())
		{
			std::cout << p1 << " wins!\n";
			Restart();
			continue;
		}

		// Player 2 logic
		std::string p2Space;
		std::cout << "P2 select a space: ";

		// Check for valid input on p2 response
		do {
			std::cin >> p2Space;
		} while (!CheckValidInput(p2Space));

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (board[i][j] == p2Space)
				{
					board[i][j] = "O";
					break;
				}
			}
		}

		PrintBoard();
		if (CheckWin())
		{
			std::cout << p2 << " wins!\n";
			Restart();
			continue;
		}
	}
	*/

	return 0;
}

void PrintBoard() {
	// Row 1
	std::cout << board[0][0] << " | ";
	std::cout << board[0][1] << " | ";
	std::cout << board[0][2] << std::endl;

	std::cout << "----------" << std::endl;

	// Row 2
	std::cout << board[1][0] << " | ";
	std::cout << board[1][1] << " | ";
	std::cout << board[1][2] << std::endl;

	std::cout << "----------" << std::endl;

	// Row 3
	std::cout << board[2][0] << " | ";
	std::cout << board[2][1] << " | ";
	std::cout << board[2][2] << std::endl << std::endl;
}

bool CheckWin() {
	bool GameOver = false;
	// 0, 0 checks
	if (board[0][0] == board[0][1] && board[0][0] == board[0][2])
	{
		std::cout << "Game over!\n";
		GameOver = true;
	}
	else if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}
	else if (board[0][0] == board[1][0] && board[0][0] == board[2][0]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}
	// 0, 1 checks
	else if (board[0][1] == board[1][1] && board[0][1] == board[2][1]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}
	// 0, 2 checks
	else if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}
	else if (board[0][2] == board[1][2] && board[0][2] == board[2][2]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}
	// 1, 0 checks
	else if (board[1][0] == board[1][1] && board[1][0] == board[1][2]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}
	// 2, 0 checks
	else if (board[2][0] == board[2][1] && board[2][0] == board[2][2]) {
		std::cout << "Game over!\n";
		GameOver = true;
	}

	return GameOver;
}

void Restart() {
	int val = 1;

	// Loop through and reset all the spaces
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			board[i][j] = std::to_string(val);
			val++;
		}
	}

	std::cout << "Game reset!\n" << std::endl;
	PrintBoard();
}

bool CheckValidInput(std::string input) {
	// Conert input to a number, then check if it is within the bounds (0 < input < 9)
	std::stringstream inp(input);
	int temp = -1;
	int trackVar = 1;
	inp >> temp;

	// Check if the input is a valid number
	if (temp < 0 || temp > 9)
	{
		std::cout << "Invalid space" << std::endl;
		return false;
	}

	// Check if the space is not occupied
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (trackVar == temp) {
				if (board[i][j] == "X" || board[i][j] == "O") {
					std::cout << "Space already claimed" << std::endl;
					return false;
				}
			}

			trackVar++;
		}
	}

	return true;
}

/***** GUI / IMAGE IMPLEMENTATION *****/
void DrawGrid() {
	// Set color to grey
	SDL_SetRenderDrawColor(gRenderer, 0xC0, 0xC0, 0xC0, 0xFF);

	// Drawing the rows
	for (size_t i = 1; i < 3; i++) {
		// (screen width / 3) * i
		int tempRow = (SCREEN_WIDTH / 3) * i;
		SDL_RenderDrawLine(gRenderer, tempRow, 0, tempRow, SCREEN_HEIGHT);
	}

	// Drawing the columns
	for (size_t i = 1; i < 3; i++) {
		int tempCol = (SCREEN_HEIGHT / 3) * i;
		SDL_RenderDrawLine(gRenderer, 0, tempCol, SCREEN_WIDTH, tempCol);
	}
}

void CellClicked(int cellWidth, int cellHeight) {
	// Changed player turn
	if (currentBoardState == RUNNING_STATE) {
		if (currentPlayer == PLAYER_X) {
			if (guiBoard[cellWidth * 3 + cellHeight] == EMPTY) {
				guiBoard[cellWidth * 3 + cellHeight] = PLAYER_X;
			}
		}
		else if (currentPlayer == PLAYER_O) {
			if (guiBoard[cellWidth * 3 + cellHeight] == EMPTY) {
				guiBoard[cellWidth * 3 + cellHeight] = PLAYER_O;
			}
		}
	} 
	else if (currentBoardState == PLAYER_O_WINS) {
		ResetGame();
	}
	else if (currentBoardState == PLAYER_X_WINS) {
		ResetGame();
	}
}

void ChangePlayerTurn() {
	if (currentPlayer == PLAYER_X) {
		currentPlayer = PLAYER_O;
	}

	else if (currentPlayer == PLAYER_O) {
		currentPlayer = PLAYER_X;
	}
}

void DrawX(int row, int column) {
	// Get the length of the side of a smaller square inside one of our cells
	const float halfBounds = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	// Center of the cell using centerX and centerY
	const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
	const float centerY = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	// Draws the top left to the bottom right
	SDL_RenderDrawLine(gRenderer, centerX - halfBounds, centerY - halfBounds, centerX + halfBounds, centerY + halfBounds);
	SDL_RenderDrawLine(gRenderer, centerX + halfBounds, centerY - halfBounds, centerX - halfBounds, centerY + halfBounds);
}

void DrawO(int row, int column) {
	// Center of the cell using centerX and centerY
	const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
	const float centerY = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

	//BresenhamDraw(centerX, centerY, 55);
	c.BresenhamCircleDraw(gRenderer, centerX, centerY, 55);
}

/*void DrawwBoard() {
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			switch (guiBoard[i * 3 + j]) {
				case PLAYER_X:
					DrawX(i, j);
					break;
				case PLAYER_O:
					//DrawO(i, j);
					db.DrawO(gRenderer, i, j);
					break;
				default:
					break;
			}
		}
	}
}*/

int GuiCheckWin(int currPlayer) {
	int column = 0;
	int row = 0;
	int diag1 = 0;
	int diag2 = 0;
	// Check if there are three in a row or a column
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (guiBoard[i * 3 + j] == currPlayer) {
				row++;
			}

			if (guiBoard[j * 3 + i] == currPlayer) {
				column++;
			}

			if (column >= 3 || row >= 3) {
				return 1;
			}
		}
		column = 0;
		row = 0;

		if (guiBoard[i * 3 + i] == currPlayer) {
			diag1++;
		}

		if (guiBoard[i * 3 + 3 - i - 1] == currPlayer) {
			diag2++;
		}
	}

	return diag1 >= 3 || diag2 >= 3;
}

void GuiReportWinningPlayer(int currPlayer) {
	currentBoardState = currPlayer;
}

void ResetGame() {
	currentPlayer = PLAYER_X;
	currentBoardState = RUNNING_STATE;
	for (size_t i = 0; i < 9; i++) {
		guiBoard[i] = EMPTY;
	}
}