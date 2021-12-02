#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <cstdint>

class Board
{
public:
	/// <summary>
	/// Tries to make a move on the board for the current player, provided it's legal
	/// </summary>
	/// <param name="layer">Layer to place on</param>
	/// <param name="row">Row to place on</param>
	/// <param name="col">Col to place on</param>
	/// <returns>True if move was successful, false otherwise</returns>
	bool makeMove(uint8_t layer, uint8_t row, uint8_t col);

private:
	// We have a playable area of 4x4x4
	uint8_t _validLayers{ 4 }, _validRows{ 4 }, _validCols{ 4 };

	// But we add a buffer row/col to each layer to prevent 4-in-a-row from wrapping across boundaries
	uint8_t _layers{ _validLayers }, _rows{ _validRows+1u }, _cols{ _validCols+1u };

	// Keep track of the current player's tokens (XOR with board to swap players)
	std::bitset<4*5*5> _currentPlayerTokens;

	// Keep track of all tokens on board, regardless of colour
	std::bitset<4*5*5> _board;

	/* Mask off our buffer rows / cols to ensure they're always 0, e.g.
	* 1 1 1 1 0
	* 1 1 1 1 0
	* 1 1 1 1 0
	* 1 1 1 1 0
	* 0 0 0 0 0 */
	std::bitset<4 * 5 * 5> _bufferMask{
		"1111011110111101111000000111101111011110111100000011110111101111011110000001111011110111101111000000"
	};
};

#endif BOARD_H