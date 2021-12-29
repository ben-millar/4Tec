#ifndef MINIMAX_H
#define MINIMAX_H

#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include <GameData.h>

using namespace std;

// A pairing of board to value
using BoardValuePair = pair<Board, int>;

class Minimax
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static Minimax* const getInstance() {
		static Minimax* const instance = new Minimax();
		return instance;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	Minimax(Minimax&) = delete;

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	Minimax& operator=(Minimax&) = delete;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_board"></param>
	/// <param name="t_player"></param>
	/// <returns></returns>
	Move findMove(Board* t_board, Board* t_player);

private:

	/// <summary>
	/// 
	/// </summary>
	Minimax() { loadWinningLines(); }

	/// <summary>
	/// 
	/// </summary>
	void loadWinningLines();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_board"></param>
	/// <param name="t_player"></param>
	/// <param name="t_depth"></param>
	/// <returns></returns>
	BoardValuePair minimax(Board& t_board, Board& t_player, int t_depth);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_board"></param>
	/// <param name="t_player"></param>
	/// <param name="t_move"></param>
	/// <returns></returns>
	int evaluate(Board& t_board, Board& t_player, Board& t_move);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	void findValidMoves(Board, vector<uint8_t>&);

	// An array of bitsets, each representing a winning line on the game board
	std::array<Board*, 76> _winningLines;
};

/// <summary>
/// Comparitor function for Board/Value pairs
/// </summary>
class Compare
{
public:
	bool operator() (BoardValuePair& p1, BoardValuePair& p2)
	{
		return p1.second < p2.second;
	}
};

#endif