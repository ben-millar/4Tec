#include <Minimax.h>
#include <iostream>
Move Minimax::findMove(Board* t_board, Board* t_player)
{
	Board bestBoard = minimax(*t_board, *t_player, 0);
	auto move = bestBoard ^ *t_board;

	int index = 0;
	for (; index < 100; ++index)
		if (move.test(index)) break;

	uint8_t layer, row, col;
	layer = index / 25;
	row = (index - layer * 25) / 5;
	col = index - (layer * 25 + row * 5);

	return Move(layer, row, col);
	//return Move();
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
		_winningLines.at(i++) = new std::bitset<4 * 5 * 5>{ line.c_str() };
	}

	input.close();
}
catch (const std::exception&)
{

}

////////////////////////////////////////////////////////////

Board Minimax::minimax(Board& t_board, Board& t_player, int t_depth)
{
	vector<uint8_t> vm;
	findValidMoves(t_board, vm);

	Board bestBoard, move;
	int bestScore = numeric_limits<int>::min();

	for (uint8_t& index : vm)
	{
		move.reset();
		move.set(index);

		int score = evaluate(t_board, t_player, move);

		if (score > bestScore)
		{
			bestBoard = (t_board | move);
			bestScore = score;
		}
	}

	return bestBoard;

	//if (t_depth > 0)
	//{
	//	// Max
	//	return *vb.begin();

	//	// Min
	//	//return *vb.end();
	//}
	//else
	//{
	//	Board* best = new Board();

	//	for (Board* b : vb)
	//	{
	//		auto res = minimax(b, t_depth + 1);
	//		best = (res->evaluate() > best->evaluate())
	//			? res
	//			: best;
	//	}

	//	return best;
	//}
}

int Minimax::evaluate(Board& t_board, Board& t_player, Board& t_move)
{
	int value{ 0 }, pCount{ 0 }, oppCount{ 0 }, _pCount{ 0 }, _oppCount{ 0 };

	Board opponent = t_player ^ t_board;

	for (auto& wl : _winningLines)
	{
		pCount = (t_player & *wl).count();
		_pCount = ((t_move | t_player) & *wl).count();

		oppCount = (opponent & *wl).count();
		_oppCount = ((t_move | opponent) & *wl).count();

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
	static bitset<4 * 5 * 5> buffer("1111110000100001000010000111111000010000100001000011111100001000010000100001111110000100001000010000");
	bitset<4 * 5 * 5> mask;
	mask.set(0);

	t_validMoves.clear();

	t_board |= buffer;

	for (uint8_t index = 0; index < 100; ++index)
	{
		if ((t_board & mask).none())
			t_validMoves.push_back(index);
		mask <<= 1;
	}
}