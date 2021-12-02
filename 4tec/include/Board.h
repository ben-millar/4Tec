#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <cstdint>

class Board
{
public:
	bool makeMove(uint8_t layer, uint8_t row, uint8_t col);
private:

	uint8_t _layers{ 4 }, _rows{ 4 }, _cols{ 4 };

	// Keep track of the current player's tokens (XOR with board to swap players)
	std::bitset<4*4*4> _currentPlayerTokens;

	// Keep track of all tokens on board, regardless of colour
	std::bitset<4*4*4> _board;
};

#endif BOARD_H