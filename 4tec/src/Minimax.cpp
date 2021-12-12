#include <Minimax.h>
#include <iostream>
Move Minimax::findMove(Board* t_board)
{
	//auto bestBoard = minimax(t_board, 0)->getBoard();
	//auto move = bestBoard ^ t_board->getBoard();

	//int index = 0;
	//for (; index < 100; ++index)
	//	if (move.test(index)) break;

	//uint8_t layer, row, col;
	//layer = index / 25;
	//row = (index - layer * 25) / 5;
	//col = index - (layer * 25 + row * 5);

	//return Move(layer, row, col);
	return Move();
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

Board* Minimax::minimax(Board* t_board, int t_depth)
{
	//auto vb = findValidMoves(t_board);

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
	return new Board();
}

int Minimax::evaluate(Board* t_board, Board* t_player)
{
	int value{ 0 }, pCount{ 0 }, oppCount{ 0 };

	Board opponent = *t_player ^ *t_board;

	for (auto& wl : _winningLines)
	{
		pCount = pow((*t_player & *wl).count(), 3);
		oppCount = -pow((opponent & *wl).count(), 3);

		if (pCount && oppCount)
			continue;
		
		value += pCount += oppCount;
	}

	return value;
}

////////////////////////////////////////////////////////////

void Minimax::findValidMoves(Board t_board, vector<uint8_t>& t_validMoves)
{
	static bitset<4 * 5 * 5> buffer("0000100001000010000111111000010000100001000011111100001000010000100001111110000100001000010000111111");
	bitset<4 * 5 * 5> mask;
	mask.set(0);

	t_validMoves.clear();

	t_board &= buffer;

	for (uint8_t index = 0; index < 100; ++index)
	{
		if ((t_board & mask).none())
			t_validMoves.push_back(index);
		mask >>= 1;
	}
}