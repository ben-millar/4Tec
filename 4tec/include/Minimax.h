#ifndef MINIMAX_H
#define MINIMAX_H

#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include <GameData.h>

using namespace std;

class Minimax
{
public:
	static Minimax* const getInstance() {
		static Minimax* const instance = new Minimax();
		return instance;
	}

	Minimax(Minimax&) = delete;
	Minimax& operator=(Minimax&) = delete;

	Move findMove(Board* t_board, Board* t_player);

private:
	Minimax() { loadWinningLines(); }

	void loadWinningLines();

	Board minimax(Board& t_board, Board& t_player, int t_depth);

	int evaluate(Board& t_board, Board& t_player, Board& t_move);

	//Board* min(vector<Board*>);
	//Board* max(vector<Board*>);
	//pair<Board*, Board*> minmax(vector<Board*>);
	void findValidMoves(Board, vector<uint8_t>&);

	// An array of bitsets, each representing a winning line on the game board
	std::array<Board*, 76> _winningLines;
};

#endif