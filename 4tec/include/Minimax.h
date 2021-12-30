#ifndef MINIMAX_H
#define MINIMAX_H

#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

// TEMP FOR DEBUGGING/OPTIMIZATION
#include <chrono>
//////////////////////////////////

#include <GameData.h>

using namespace std;
using namespace std::chrono;

// A pairing of board to value
using MoveValuePair = pair<uint8_t, int>;

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
	MoveValuePair minimax(Board& t_board, Board& t_player, int t_depth);

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

	const int MAX_DEPTH{ 2 };

	// An array of bitsets, each representing a winning line on the game board
	std::array<Board*, 76> _winningLines;
};

/// <summary>
/// Comparitor function for Board/Value pairs
/// </summary>
class Compare
{
public:
	bool operator() (MoveValuePair& p1, MoveValuePair& p2)
	{
		return p1.second < p2.second;
	}
};

#endif