#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include <GameData.h>

class BoardManager
{
public:
	BoardManager();

	/// <summary>
	/// Tries to make a move on the board for the current player, provided it's legal
	/// </summary>
	void makeMove(Board& t_board, Move t_move);
	
	/// <summary>
	/// Given a board position, checks if a valid move can be played there.
	/// </summary>
	bool isValid(Board& t_board, Move t_move);

	bool checkForWin(Board& t_board, Board& t_win);

private:
	void loadWinningLines();

	uint8_t moveToIndex(Move t_move);

	// We have a playable area of 4x4x4
	uint8_t _layers{ 4 }, _rows{ 4 }, _cols{ 4 };

	// An array of bitsets, each representing a winning line on the game board
	std::array<Board*, 76> _winningLines;
};

#endif BOARD_H