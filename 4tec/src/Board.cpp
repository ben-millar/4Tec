#include <Board.h>
#include <iostream>

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
		uint8_t(down + horizontal-2), // Backwards
		uint8_t(down + vertical),
		uint8_t(down - vertical), // Backwards
		uint8_t(down + DR),
		uint8_t(down - DR),
		uint8_t(down + DL),
		uint8_t(down - DL)
	};

	loadWinningLines();
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

		std::cout << evaluate() << std::endl;

		if (checkForWin())
			std::cout << "WEENER \n";
			// **************** DO SOMETHING HERE ****************

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////

int Board::evaluate()
{
	int count = 0;
	auto lp = _currentPlayerTokens ^ _board;

	for (auto& line : _winningLines)
		if ((*line & lp).any() && (_currentPlayerTokens & *line).none())
			count++;

	return count;
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

////////////////////////////////////////////////////////////

void Board::loadWinningLines()
{
	std::string file_path = "assets/data/winning_lines.txt", line;
	std::ifstream input(file_path.c_str(), std::ifstream::in);

	if (input.is_open())
		std::perror("Error opening file in Board.cpp");

	int i = 0;

	while (std::getline(input, line))
	{
		// Flip string (bitset initialises from right-to-left
		std::reverse(line.begin(), line.end());
		_winningLines.at(i++) = new std::bitset<4 * 5 * 5>{ line.c_str() };
	}
		

	input.close();
}
