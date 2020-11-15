#pragma once

class Game
{

public:
	int iCurrentBoardState;

private:
	enum GAME_STATE {
		RUNNING_STATE = 0,
		PLAYER_X_WINS = 1,
		PLAYER_O_WINS = 2,
		TIE = 3,
		QUIT = 4
	};

	enum BOARD_ENTRY {
		EMPTY = 0,
		PLAYER_X = 1,
		PLAYER_O = 2
	};

	int guiBoard[9] = {
		EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY
	};

	int N = 3;

	void CellClicked(int cellWidth, int cellHeight);
};

