#include "Board.h"
#include "..\include\Board.h"

bool Board::makeMove(uint8_t layer, uint8_t row, uint8_t col)
{
	if (layer > _validLayers || row > _validRows || col > _validCols)
		return false;

	// E.g., 1/1/1 = 1(16) + 1(4) + 1 = 21
	uint8_t index =
		layer * (_rows * _cols) +	// Layer * cells per layer
		row * (_cols) +				// Row * cells per row
		col;						// Col on row

	// If there's nothing in this cell
	if (!_board.test(index))
	{
		// XOR to the next player before modifying the board
		_currentPlayerTokens ^= _board;

		// Add last player's token
		_board.set(index, true);

		// Ensure buffer rows/cols are 0 (is this necessary?)
		_board &= _bufferMask;

		return true;
	}

	return false;
}