#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <algorithm>
#include <bitset>
#include <cstdint>
#include <fstream>
#include <string>

class Board
{
public:
	Board();

	/// <summary>
	/// Tries to make a move on the board for the current player, provided it's legal
	/// </summary>
	/// <param name="layer">Layer to place on</param>
	/// <param name="row">Row to place on</param>
	/// <param name="col">Col to place on</param>
	/// <returns>True if move was successful, false otherwise</returns>
	bool makeMove(uint8_t layer, uint8_t row, uint8_t col);

	int evaluate();

	bool checkForWin();

private:
	void loadWinningLines();

	// We have a playable area of 4x4x4
	uint8_t _validLayers{ 4 }, _validRows{ 4 }, _validCols{ 4 };

	// But we add a buffer row/col to each layer to prevent 4-in-a-row from wrapping across boundaries
	uint8_t _layers{ _validLayers }, _rows{ _validRows+1u }, _cols{ _validCols+1u };

	// The set of strides through our bitset we need to check to find 4-in-a-rows
	std::array<uint8_t, 13> _offsets;

	// Keep track of the current player's tokens (XOR with board to swap players)
	std::bitset<4*5*5> _currentPlayerTokens;

	// Keep track of all tokens on board, regardless of colour
	std::bitset<4*5*5> _board;

	// An array of bitsets, each representing a winning line on the game board
	std::array<std::bitset<4*5*5>*, 76> _winningLines;
};

#endif BOARD_H