#include <iostream>
#include "TTTGame.h"
#include <stdlib.h>

void twoPlayerMode(int boardSize, int winningCombo);
void simpleAIMode(int boardSize, int winningCombo);
void smartAIMode(int boardSize, int winningCombo);

int main()
{
	bool menu=true;
	int mode,boardSize,winningCombo;
	while (menu)
	{
		system("CLS");
		std::cout << "TIC TAC TOE GAME\n";
		std::cout << "1 - two player mode\n";
		std::cout << "2 - simpleAI mode\n";
		std::cout << "3 - smartAI mode\n";
		std::cout << "0 - quit\n";
		std::cout << "Select mode: ";
		std::cin >> mode;
		switch (mode)
		{
		case 0:
			menu = 0;
			break;
		case 1:
			system("CLS");
			std::cout << "Enter board size: ";
			std::cin >> boardSize;
			std::cout << "Enter winning combo: ";
			std::cin >> winningCombo;
			twoPlayerMode(boardSize, winningCombo);
			std::cout << "Press enter to go back to menu\n";
			std::cin.get();
			std::cin.get();
			break;
		case 2:
			system("CLS");
			std::cout << "Enter board size: ";
			std::cin >> boardSize;
			std::cout << "Enter winning combo: ";
			std::cin >> winningCombo;
			simpleAIMode(boardSize, winningCombo);
			std::cout << "Press enter to go back to menu\n";
			std::cin.get();
			std::cin.get();
			break;
		case 3:
			system("CLS");
			std::cout << "Enter board size: ";
			std::cin >> boardSize;
			std::cout << "Enter winning combo: ";
			std::cin >> winningCombo;
			smartAIMode(boardSize, winningCombo);
			std::cout << "Press enter to go back to menu\n";
			std::cin.get();
			std::cin.get();
			break;
		default:
			break;
		}
	}
}

void twoPlayerMode(int boardSize, int winningCombo)
{
	TTTGame TTT(boardSize,winningCombo);
	int player, boxNumberInput;
	int clickCounter = 0;
	while (1)
	{
		system("CLS");
		TTT.printBoard();
		player = clickCounter % 2;

		if (player == 1) std::cout << "Player X turn\n";
		if (player == 0) std::cout << "Player O turn\n";

		std::cout << "Insert box number: ";
		std::cin >> boxNumberInput;
		if (TTT.handleTurn(player, boxNumberInput))
			clickCounter++;

		int win = TTT.winStatus(player);
		if (win == 1)
		{
			system("CLS");
			TTT.printBoard();
			if (player == 1) std::cout << "Player X won\n";
			if (player == 0) std::cout << "Player O won\n";
			break;
		}
		else if(win == 0)
		{
			system("CLS");
			TTT.printBoard();
			std::cout << "DRAW\n";
			break;
		}
		std::cout << std::endl;
	}
}

void simpleAIMode(int boardSize, int winningCombo)
{
	TTTGame TTT(boardSize, winningCombo);
	int player, boxNumberInput;
	int turnCounter = 0;
	while (1)
	{
		system("CLS");
		TTT.printBoard();
		player = turnCounter % 2;

		if (player == 1) std::cout << "Player X turn\n";

		if (player == 1)
		{
			std::cout << "Insert box number: ";
			std::cin >> boxNumberInput;
			if (TTT.handleTurn(player, boxNumberInput))
				turnCounter++;
		}
		if (player == 0)
		{
			TTT.simpleAI(player);
			turnCounter++;
		}

		int win = TTT.winStatus(player);
		if (win == 1)
		{
			system("CLS");
			TTT.printBoard();
			if (player == 1) std::cout << "Player X won\n";
			if (player == 0) std::cout << "Player O won\n";
			break;
		}
		else if (win == 0)
		{
			system("CLS");
			TTT.printBoard();
			std::cout << "DRAW\n";
			break;
		}
		std::cout << std::endl;
	}
}

void smartAIMode(int boardSize, int winningCombo)
{
	TTTGame TTT(boardSize, winningCombo);
	int player, boxNumberInput;
	int turnCounter = 0;
	while (1)
	{
		system("CLS");
		TTT.printBoard();
		TTT.log();
		player = turnCounter % 2;

		if (player == 1) std::cout << "Player X turn\n";

		if (player == 1)
		{
			std::cout << "Insert box number: ";
			std::cin >> boxNumberInput;
			if (TTT.handleTurn(player, boxNumberInput))
				turnCounter++;
		}
		if (player == 0)
		{
			TTT.smartAI(player);
			turnCounter++;
		}

		int win = TTT.winStatus(player);
		if (win == 1)
		{
			system("CLS");
			TTT.printBoard();
			if (player == 1) std::cout << "Player X won\n";
			if (player == 0) std::cout << "Player O won\n";
			break;
		}
		else if (win == 0)
		{
			system("CLS");
			TTT.printBoard();
			std::cout << "DRAW\n";
			break;
		}
		std::cout << std::endl;
	}
}


