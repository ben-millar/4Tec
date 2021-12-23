#include <BoardManager.h>

BoardManager::BoardManager()
{
	loadWinningLines();
}

////////////////////////////////////////////////////////////

void BoardManager::loadWinningLines()
try
{
	std::string file_path = "assets/data/winning_lines.txt", line;
	std::ifstream input(file_path.c_str(), std::ifstream::in);

	if (!input.is_open())
		std::perror("Error opening file in BoardManager.cpp");

	int i = 0;

	while (std::getline(input, line))
	{
		// Flip string (bitset initialises from right-to-left
		std::reverse(line.begin(), line.end());
		_winningLines.at(i++) = new Board{ line.c_str() };
	}

	input.close();
}
catch (const std::exception&)
{

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

	if (layer >= _layers || row >= _rows || col >= _cols)
		return false;

	uint8_t index = moveToIndex(t_move);

	return !t_board.test(index);
}

////////////////////////////////////////////////////////////

bool BoardManager::checkForWin(Board& t_board)
{
	for (auto& wl : _winningLines)
		if (4 == (t_board & *wl).count())
			return true;

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