#include "TTTGame.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
void TTTGame::putNumberOnBoard(int verticalIndex, int horizontalIndex, int number)
{
	int units, dozens, hundreds;
	int tmpNumber = number;
	units = tmpNumber % 10;
	tmpNumber = tmpNumber / 10;
	dozens = tmpNumber % 10;
	tmpNumber = tmpNumber / 10;
	hundreds = tmpNumber % 10;

	if (number < 10)
	{
		std::string s = std::to_string(units);
		m_board[verticalIndex][horizontalIndex] = *s.c_str();
	}
	if (number > 9)
	{
		std::string d = std::to_string(dozens);
		m_board[verticalIndex][horizontalIndex] = *d.c_str();
		std::string u = std::to_string(units);
		m_board[verticalIndex][horizontalIndex+1] = *u.c_str();
	}

}

int TTTGame::miniMax(int depth, int maxDepth, int player, bool maximizer)
{
	if (depth == maxDepth)
	{
		return 0;
	}
	int bestValue,verticalIndex,horizontalIndex,moveValue;
	int win = winStatus(player);
	if (win != -1)
	{
		if (win == 0)
			return 0;
		if (win == 1 && player == 0)
			return 1;
		if (win == 1 && player == 1)
			return -1;
	}
	

	if (maximizer)
	{
		bestValue = -1000;
		for (int boxNumber = 1; boxNumber < m_boardSize*m_boardSize+1; boxNumber++)
		{
			verticalIndex = (boxNumber - 1) / m_boardSize;
			horizontalIndex = (boxNumber - 1) % m_boardSize;
			if (m_TTTBoard[verticalIndex][horizontalIndex] == 0)
			{
				m_TTTBoard[verticalIndex][horizontalIndex] = 1;
				moveValue = miniMax(depth+1,maxDepth, 0,!maximizer);
				m_TTTBoard[verticalIndex][horizontalIndex] = 0;
				bestValue = std::max(moveValue,bestValue);
			}
		}
		return bestValue;
	}
	else
	{
		bestValue = 10000;
		for (int boxNumber = 1; boxNumber < m_boardSize * m_boardSize + 1; boxNumber++)
		{
			verticalIndex = (boxNumber - 1) / m_boardSize;
			horizontalIndex = (boxNumber - 1) % m_boardSize;
			if (m_TTTBoard[verticalIndex][horizontalIndex] == 0)
			{
				m_TTTBoard[verticalIndex][horizontalIndex] = 2;
				moveValue = miniMax(depth + 1,maxDepth, 1, !maximizer);
				m_TTTBoard[verticalIndex][horizontalIndex] = 0;
				bestValue = std::min(moveValue, bestValue);
			}
		}
		return bestValue;
	}
}

TTTGame::TTTGame()
{
	m_boardSize = 3;
	m_verticalSize = 4 * m_boardSize + 1;
	m_horizontalSize = 6 * m_boardSize + 1;
	m_winningCombo = 3;
	m_gameInfo = "";

	//m_board initialization
	m_board = new char*[m_verticalSize];
	for (int i = 0; i < m_verticalSize; i++)
		m_board[i] = new char[m_horizontalSize];
	
	for (int i = 0; i < m_verticalSize; i++)
		for (int j = 0; j < m_horizontalSize; j++)
			m_board[i][j] = ' ';
	int boxCounter = 1;
	for (int i = 0; i < m_verticalSize; i++)
	{
		for (int j = 0; j < m_horizontalSize; j++)
		{
			if (i % 4 == 0) m_board[i][j] = '-';
			else
			{
				if (j % 6 == 0)
				{
					m_board[i][j] = '|';
					if ((i - 1) % 4 == 0)
					{
						if (j < m_horizontalSize-1)
						{
							putNumberOnBoard(i, j + 1, boxCounter);
							boxCounter++;
						}
					}
				}
			}	
		}
	}

	//m_TTTBoard initialization
	m_TTTBoard = new int* [m_boardSize];
	for (int i = 0; i < m_boardSize; i++)
		m_TTTBoard[i] = new int[m_boardSize];

	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			m_TTTBoard[i][j] = 0;
		}
	}
}

TTTGame::TTTGame(int boardSize,int winningCombo)
{
	m_boardSize = boardSize;
	m_verticalSize = 4 * m_boardSize + 1;
	m_horizontalSize = 6 * m_boardSize + 1;
	m_winningCombo = winningCombo;
	m_gameInfo = "";
	//m_board initialization
	m_board = new char* [m_verticalSize];
	for (int i = 0; i < m_verticalSize; i++)
		m_board[i] = new char[m_horizontalSize];

	for (int i = 0; i < m_verticalSize; i++)
		for (int j = 0; j < m_horizontalSize; j++)
			m_board[i][j] = ' ';
	int boxCounter = 1;
	for (int i = 0; i < m_verticalSize; i++)
	{
		for (int j = 0; j < m_horizontalSize; j++)
		{
			if (i % 4 == 0) m_board[i][j] = '-';
			else
			{
				if (j % 6 == 0)
				{
					m_board[i][j] = '|';
					if ((i - 1) % 4 == 0)
					{
						if (j < m_horizontalSize - 1)
						{
							putNumberOnBoard(i, j + 1, boxCounter);
							boxCounter++;
						}
					}
				}
			}
		}
	}

	//m_TTTBoard initialization
	m_TTTBoard = new int* [m_boardSize];
	for (int i = 0; i < m_boardSize; i++)
		m_TTTBoard[i] = new int[m_boardSize];

	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			m_TTTBoard[i][j] = 0;
		}
	}
}

void TTTGame::printBoard()
{
	for (int i = 0; i < m_verticalSize; i++)
	{
		for (int j = 0; j < m_horizontalSize; j++)
			std::cout << m_board[i][j];		
		std::cout << std::endl;
	}
	std::cout << m_gameInfo;
	m_gameInfo = "";
}

void TTTGame::log()
{
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
			std::cout << m_TTTBoard[i][j];
		std::cout << std::endl;
	}
}

void TTTGame::putSign(int boxNumber, int player)
{
	int verticalIndex = ((boxNumber - 1) / m_boardSize) * 4 + 2;
	int horizontalIndex = ((boxNumber - 1) % m_boardSize) * 6 + 3;

	if (player == 1)
		m_board[verticalIndex][horizontalIndex] = 'X';
	else
	{
		m_board[verticalIndex][horizontalIndex] = 'O';
	}
}

bool TTTGame::handleTurn(int player, int boxNumber)
{
	if (boxNumber > m_boardSize * m_boardSize)
	{
		m_gameInfo = "You picked worng box number\n";
		return false;
	}

	int verticalIndex = (boxNumber - 1) / m_boardSize;
	int hoizontalIndex = (boxNumber - 1) % m_boardSize;
	if (m_TTTBoard[verticalIndex][hoizontalIndex] == 0)
	{
		switch (player)
		{
		case 0:
			putSign(boxNumber,player);
			m_TTTBoard[verticalIndex][hoizontalIndex] = 1;
			break;
		case 1:
			putSign(boxNumber, player);
			m_TTTBoard[verticalIndex][hoizontalIndex] = 2;
			break;
		default:
			break;
		}
		return true;
	}
	else
	{
		m_gameInfo = "This field is already selected\n";
		return false;
	}
}

int TTTGame::winStatus(int player)
{
	//poziom
	int winningStreak = 0;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			if (m_TTTBoard[i][j] == player + 1)
			{
				winningStreak++;
			}
			else
			{
				winningStreak = 0;
			}
			if (winningStreak == m_winningCombo)
			{
				return 1;
			}
		}
		winningStreak = 0;
	}

	//pion
	winningStreak = 0;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			if (m_TTTBoard[j][i] == player + 1)
			{
				winningStreak++;
			}
			else
			{
				winningStreak = 0;
			}
			if (winningStreak == m_winningCombo)
			{
				return 1;
			}
		}
		winningStreak = 0;
	}

	//skos1
	winningStreak = 0;
	int verticalIndex, horizontalIndex;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			verticalIndex = i;
			horizontalIndex = j;
			winningStreak = 0;
			while (verticalIndex < m_boardSize && horizontalIndex < m_boardSize)
			{
				if (m_TTTBoard[verticalIndex][horizontalIndex] == player + 1)
				{
					winningStreak++;
				}
				else
				{
					winningStreak = 0;
				}
				if (winningStreak == m_winningCombo)
				{
					return 1;
				}
				verticalIndex++;
				horizontalIndex++;
			}
		}
	}

	//skos2
	winningStreak = 0;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			verticalIndex = i;
			horizontalIndex = j;
			winningStreak = 0;
			while (verticalIndex > -1 && horizontalIndex < m_boardSize)
			{
				if (m_TTTBoard[verticalIndex][horizontalIndex] == player + 1)
				{
					winningStreak++;
				}
				else
				{
					winningStreak = 0;
				}
				if (winningStreak == m_winningCombo)
				{
					return 1;
				}
				verticalIndex--;
				horizontalIndex++;
			}
		}
	}

	bool tie = true;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			if (m_TTTBoard[i][j] == 0)
				tie = false;
		}
	}
	if (tie) return 0;
	
	return -1;
}

void TTTGame::simpleAI(int player)
{
	int boxNumber,verticalIndex,horizontalIndex;

	srand(time(NULL));
	do
	{
		boxNumber= (rand() % (m_boardSize*m_boardSize))+1;
		verticalIndex = (boxNumber - 1) / m_boardSize;
		horizontalIndex = (boxNumber - 1) % m_boardSize;

	} while (m_TTTBoard[verticalIndex][horizontalIndex] != 0);
	putSign(boxNumber, player);
	m_TTTBoard[verticalIndex][horizontalIndex] = player + 1;
}

void TTTGame::smartAI(int player)
{
	int moveValue;
	int bestValue = -10000;
	int bestMove;
	int verticalIndex;
	int horizontalIndex;

	for (int  boxNumber = 1; boxNumber < m_boardSize*m_boardSize+1; boxNumber++)
	{
		verticalIndex = (boxNumber - 1) / m_boardSize;
		horizontalIndex = (boxNumber - 1) % m_boardSize;
		if (m_TTTBoard[verticalIndex][horizontalIndex] == 0)
		{
			m_TTTBoard[verticalIndex][horizontalIndex] = 1;
			moveValue = miniMax(0,4,0,false);
			m_TTTBoard[verticalIndex][horizontalIndex] = 0;
			if (moveValue > bestValue)
			{
				bestValue = moveValue;
				bestMove = boxNumber;
			}
		}
	}
	putSign(bestMove, player);
	verticalIndex = (bestMove - 1) / m_boardSize;
	horizontalIndex = (bestMove - 1) % m_boardSize;
	m_TTTBoard[verticalIndex][horizontalIndex] = player + 1;
}

TTTGame::~TTTGame()
{
	for (int i = 0; i < 4 * m_boardSize + 1; i++)
		delete[] m_board[i];
	delete[] m_board;

	for (int i = 0; i < m_boardSize; i++)
		delete[] m_TTTBoard[i];
	delete[] m_TTTBoard;
}
