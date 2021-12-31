#include <Minimax.h>

Move Minimax::findMove(Board* t_board, Board* t_player)
{
	uint8_t move_index;

	if (_lookupTable.count(*t_board))
	{
		move_index = _lookupTable.at(*t_board);
		cout << "Cache hit\n";
	}
	else
	{
		// Retrieve the board, discard the value
		move_index = minimax(*t_board, *t_player, 0, AlphaBeta()).first;
	}
	//uint8_t move_index = 
	//	_lookupTable.count(*t_board)
	//	? _lookupTable.at(*t_board)
	//	: minimax(*t_board, *t_player, 0, AlphaBeta()).first;

	

	uint8_t layer, row, col;
	layer = move_index / 16;
	row = (move_index - layer * 16) / 4;
	col = move_index - (layer * 16 + row * 4);

	return Move(layer, row, col);
}

////////////////////////////////////////////////////////////

void Minimax::loadWinningLines()
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

void Minimax::loadLookupTable()
try
{
	std::string file_path = "assets/data/lookup_table.txt", line, key, response;
	std::ifstream input(file_path.c_str(), std::ifstream::in);

	if (!input.is_open())
		std::perror("Error opening file in Minimax.cpp");

	int i = 0;

	while (std::getline(input, line))
	{
		stringstream ss(line);
		std::getline(ss, key, ',');
		std::getline(ss, response, ',');

		_lookupTable.emplace(Board(stoull(key)), stoi(response));
	}

	input.close();
}
catch (const std::exception&)
{

}

////////////////////////////////////////////////////////////

MoveValuePair Minimax::minimax(Board& t_board, Board& t_player, int t_depth, AlphaBeta t_ab)
{
	vector<uint8_t> vm;
	findValidMoves(t_board, vm);

	bool isMinimizer = t_depth % 2;

	if (t_depth < MAX_DEPTH)
	{
		MoveValuePair best = { -1, 2147483647 };
		MoveValuePair worst = { -1, -2147483647 };

		for (uint8_t& index : vm)
		{
			MoveValuePair value = minimax(t_board, t_player, t_depth + 1, t_ab);

			if (isMinimizer)
			{
				if (shouldPrune(value, best, t_ab, isMinimizer))
					break;
			}
			else
			{
				if (shouldPrune(value, worst, t_ab, isMinimizer))
					break;
			}
		}

		return isMinimizer
			? best
			: worst;
	}

	Board move;
	vector<MoveValuePair> rankedMoves;

	for (uint8_t& index : vm)
	{
		move.reset();
		move.set(index);

		rankedMoves.push_back({ index, evaluate(t_board, t_player, move) });
	}

	return *max_element(rankedMoves.begin(), rankedMoves.end(), Compare());
}

////////////////////////////////////////////////////////////

int Minimax::evaluate(Board& t_board, Board& t_player, Board& t_move)
{
	int value{ 0 }, pCount{ -1 }, _pCount{ -1 }, oppCount{ -1 };

	Board opponent = t_player ^ t_board;

	for (auto& wl : _winningLines)
	{
		pCount = (t_player & *wl).count();				// Before move
		oppCount = (opponent & *wl).count();			// Before move
		
		// Ignore line if both players have tokens; unwinnable.
		if (pCount && oppCount)
			continue;

		// If we have 3 tokens on this line, and our token completes the line
		// we've won the game on this turn.
		if (3 == pCount)
			// We only initialise _pCount if we make it to this if condition
			if (4 == (_pCount = ((t_move | t_player) & *wl).count()))
				return 2147483647;

		// If the opponent has 3 tokens on this line, and our token completes the line
		// we've blocked an opponent win this turn.
		if (3 == oppCount)
			if (4 == ((t_move | opponent) & *wl).count())
				return 1073741823;

		// Add a value for adding to a free line, skewed towards longer lengths
		value +=
			-1 == _pCount // Only run .count() if it hasn't been worked out previously
			? (_pCount = ((t_move | t_player) & *wl).count()) << _pCount
			: _pCount << _pCount;

		_pCount = -1;
	}

	return value;
}

////////////////////////////////////////////////////////////

bool Minimax::shouldPrune(MoveValuePair& t_value, MoveValuePair& t_best, AlphaBeta& t_ab, bool isMinimizer)
{
	if (isMinimizer)
	{
		t_best = min(t_best, t_value);
		t_ab.beta = std::min(t_ab.beta, t_best.second);
		return (t_ab.beta <= t_ab.alpha);
	}
	else
	{
		t_best = max(t_best, t_value);
		t_ab.alpha = std::max(t_ab.alpha, t_best.second);
		return (t_ab.beta <= t_ab.alpha);
	}

	return false;
}

////////////////////////////////////////////////////////////

void Minimax::findValidMoves(Board t_board, vector<uint8_t>& t_validMoves)
{
	Board mask;
	mask.set(0);

	t_validMoves.clear();

	for (uint8_t index = 0; index < t_board.size(); ++index)
	{
		if ((t_board & mask).none())
			t_validMoves.push_back(index);
		mask <<= 1;
	}
}