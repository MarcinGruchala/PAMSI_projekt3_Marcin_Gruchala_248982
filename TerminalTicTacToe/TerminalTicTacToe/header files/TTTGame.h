#pragma once
#include <string>
struct move
{
	int boxNumber;
	int verticalIndex;
	int horizontalIndex;
};

class TTTGame
{
private:
	int m_boardSize;
	int m_verticalSize;
	int m_horizontalSize;
	char** m_board;
	int** m_TTTBoard;
	int m_playerTurn;
	int m_winningCombo;
	
	std::string m_gameInfo;

	void putNumberOnBoard(int verticalIndex, int horizontalIndex, int number);
	int miniMax(int depth,int maxDepth,int player, bool maximizer);


public:
	TTTGame();
	TTTGame(int boardSize, int winningCombo);
	void printBoard();
	void log();
	void putSign(int boxNumber, int player);
	bool handleTurn(int player, int boxNumber);
	int	 winStatus(int player);
	void simpleAI(int player);
	void smartAI(int player);
	~TTTGame();
};
