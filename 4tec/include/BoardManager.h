#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <array>
#include <algorithm>
#include <bitset>
#include <cstdint>

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


	bool checkForWin(Board& t_board);

private:
	

	uint8_t moveToIndex(Move t_move);

	// We have a playable area of 4x4x4
	uint8_t _validLayers{ 4 }, _validRows{ 4 }, _validCols{ 4 };

	// But we add a buffer row/col to each layer to prevent 4-in-a-row from wrapping across boundaries
	uint8_t _layers{ _validLayers }, _rows{ _validRows+1u }, _cols{ _validCols+1u };

	// The set of strides through our bitset we need to check to find 4-in-a-rows
	std::array<uint8_t, 13> _offsets;
};

#endif BOARD_H