#include <Board.h>

Board::Board()
{
	// Bit Offsets
	uint8_t horizontal = 1u; // Along a row
	uint8_t vertical = _cols; // Along a column
	uint8_t DR = _cols + 1; // Down-right diagonal
	uint8_t DL = _cols - 1; // Down-left diagonal
	uint8_t down = _rows * _cols; // Between layers

	_offsets = {
		// On board
		horizontal,
		vertical,
		DR,
		DL,
		// Across boards
		down,
		uint8_t(down + horizontal),
		uint8_t(down + vertical),
		uint8_t(down + DR),
		uint8_t(down + DL)
	};
}

////////////////////////////////////////////////////////////

bool Board::makeMove(uint8_t layer, uint8_t row, uint8_t col)
{
	 if (layer >= _validLayers || row >= _validRows || col >= _validCols)
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

		if (checkForWin())
			// **************** DO SOMETHING HERE ****************

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////

bool Board::checkForWin()
{
	// Last player
	auto lp = _currentPlayerTokens ^ _board;
	std::bitset<4 * 5 * 5> mask;

	for (uint8_t& offset : _offsets)
	{
		mask = lp & (lp >> offset);
		mask = mask & (mask >> offset * 2);

		if (mask.any())
			return true;
	}

	return false;
}