#include <BoardManager.h>
#include <iostream>

BoardManager::BoardManager()
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
		uint8_t(down + horizontal-2), // Backwards
		uint8_t(down + vertical),
		uint8_t(down - vertical), // Backwards
		uint8_t(down + DR),
		uint8_t(down - DR),
		uint8_t(down + DL),
		uint8_t(down - DL)
	};
}

////////////////////////////////////////////////////////////

void BoardManager::makeMove(Board& t_board, Move t_move)
{
	t_board.set(moveToIndex(t_move), true);
}

////////////////////////////////////////////////////////////

bool BoardManager::isValid(Board& t_board, Move t_move)
{
	uint8_t layer, row, col;
	std::tie(layer, row, col) = t_move;

	if (layer >= _validLayers || row >= _validRows || col >= _validCols)
		return false;

	uint8_t index =
		layer * (_rows * _cols) +
		row * (_cols)+
		col;

	return !t_board.test(index);
}

////////////////////////////////////////////////////////////

bool BoardManager::checkForWin(Board& t_board)
{
	std::bitset<4 * 5 * 5> mask;

	for (uint8_t& offset : _offsets)
	{
		mask = t_board & (t_board >> offset);
		mask = mask & (mask >> offset * 2);

		if (mask.any())
			return true;
	}

	return false;
}

////////////////////////////////////////////////////////////

uint8_t BoardManager::moveToIndex(Move t_move)
{
	uint8_t layer, row, col;
	std::tie(layer, row, col) = t_move;

	return
		layer * (_rows * _cols) +	// Layer * cells per layer
		row * (_cols)+				// Row * cells per row
		col;						// Col on row
}