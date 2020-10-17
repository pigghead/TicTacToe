// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>

std::string board[3][3] = { {"1","2","3"}, 
							{"4","5","6"}, 
							{"7","8","9"} 
};

// Print the board and its current layout
void PrintBoard();
// Check if there is a row of three
bool CheckWin();
// Reset the board
void Restart();
// Check valid player input
bool CheckValidInput(std::string input);

bool quit = false;

int main() {

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