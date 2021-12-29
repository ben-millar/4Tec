#include <Minimax.h>
#include <iostream>
Move Minimax::findMove(Board* t_board, Board* t_player)
{
	// Retrieve the board, discard the value
	Board move = minimax(*t_board, *t_player, 0).first;

	int index = 0;

	for (; index < 64; ++index)
		if (move.test(index)) break;

	uint8_t layer, row, col;
	layer = index / 16;
	row = (index - layer * 16) / 4;
	col = index - (layer * 16 + row * 4);

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

BoardValuePair Minimax::minimax(Board& t_board, Board& t_player, int t_depth)
{
	vector<uint8_t> vm;
	findValidMoves(t_board, vm);

	Board move;

	vector<BoardValuePair> rankedMoves;

	for (uint8_t& index : vm)
	{
		move.reset();
		move.set(index);

		rankedMoves.push_back({ move, evaluate(t_board, t_player, move) });
	}

	/* We could use a priority queue here, but that is only more efficient if we 
	   need the vector to be sorted at all times. Given that we know we will only
	   be inserting at the end of our vector, it's quicker to sort at the end. */
	sort(rankedMoves.begin(), rankedMoves.end(), Compare());

	return rankedMoves.back();
}

////////////////////////////////////////////////////////////

int Minimax::evaluate(Board& t_board, Board& t_player, Board& t_move)
{
	int value{ 0 }, pCount{ 0 }, oppCount{ 0 }, _pCount{ 0 }, _oppCount{ 0 };

	Board opponent = t_player ^ t_board;

	for (auto& wl : _winningLines)
	{
		pCount = (t_player & *wl).count();				// Before move
		_pCount = ((t_move | t_player) & *wl).count();	// After move

		oppCount = (opponent & *wl).count();			// Before move
		_oppCount = ((t_move | opponent) & *wl).count();// After move

		// This move wins the game
		if (3 == pCount)
			if (4 == _pCount)
				return std::numeric_limits<int>::max();

		// This move blocks an opponents win
		if (3 == oppCount)
			if (4 == _oppCount)
				return std::numeric_limits<int>::max() / 2;

		// Ignore line if both players have tokens; unwinnable.
		if (pCount && oppCount)
			continue;

		// Add a value for adding to a free line, skewed towards longer lengths
		pCount = pow(_pCount, 4.f);
		
		value += pCount;
	}

	return value;
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