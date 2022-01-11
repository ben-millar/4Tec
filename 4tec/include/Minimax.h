#ifndef MINIMAX_H
#define MINIMAX_H

#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include <GameData.h>

#include <chrono>

using namespace std;
using namespace std::chrono;

// A pairing of board to value
using MoveValuePair = pair<uint8_t, int>;

class Minimax
{
public:
	/// <summary>
	/// Return instance of Minimax singleton
	/// </summary>
	/// <returns>Pointer to a static instance of Minimax</returns>
	static Minimax* const getInstance() {
		static Minimax* const instance = new Minimax();
		return instance;
	}

	/// <summary>
	/// Explicitly delete copy constructor
	/// </summary>
	Minimax(Minimax&) = delete;

	/// <summary>
	/// Explicitly delete assignment constructor
	/// </summary>
	Minimax& operator=(Minimax&) = delete;

	/// <summary>
	/// Find the optimal move on a given board
	/// </summary>
	/// <param name="t_board">Board: Gameboard on which to find the move</param>
	/// <param name="t_player">Board: Location of the players tokens</param>
	/// <returns>The optimal move as a Move(layer, row, col)</returns>
	Move findMove(Board* t_board, Board* t_player);

private:
	/// <summary>
	/// Simple data structure for alpha/beta pruning
	/// </summary>
	struct AlphaBeta {
		int alpha{ -2147483647 };
		int beta{ 2147483647 };
	};

	/// <summary>
	/// Default c'tor, calls loadWinningLines
	/// </summary>
	Minimax() { loadWinningLines(); }

	/// <summary>
	/// Loads the winning lines (bitsets with winning combos set) from text file
	/// </summary>
	void loadWinningLines();

	/// <summary>
	/// Recursive minimax algorithm which determines the best move for a given board
	/// implements alpha-beta pruning
	/// </summary>
	/// <param name="t_board">Board: Gameboard on which to find move</param>
	/// <param name="t_player">Board: Location of the players tokens</param>
	/// <param name="t_depth">int: Depth of node currently being explored</param>
	/// <returns>An std::pair of move:value, containing the index of the best move and it's value</returns>
	MoveValuePair minimax(Board& t_board, Board& t_player, int t_depth, AlphaBeta t_ab);

	/// <summary>
	/// Evaluates a given move for a given board.
	/// A winning move returns numeric_limit<int>::max(), blocking an opponents win returns half max.
	/// All other moves are scored based on the numbers of ways they could be used to win, with a bias
	/// for longer lines (I.e. 3 in a row is worth more than twice as much as 2 in a row)
	/// </summary>
	/// <param name="t_board">Board: Gameboard on which to base evaluation on</param>
	/// <param name="t_player">Board: Location of already placed moves</param>
	/// <param name="t_move">Board: A board object containing only the move to evaluate</param>
	/// <returns>An integer score for the given move on the given board</returns>
	int evaluate(Board& t_board, Board& t_player, Board& t_move);

	/// <summary>
	/// Determine if a given subtree should be pruned using alpha-beta pruning
	/// </summary>
	/// <param name="t_value">Best-case value of the subtree</param>
	/// <param name="t_best">Best value seen so far (highest for max, lowest for min)</param>
	/// <param name="t_ab">Alpha-beta value for the given node</param>
	/// <param name="isMinimizer">True is this is MIN, false if this is MAX</param>
	/// <returns>Whether or not the subtree should be pruned</returns>
	bool shouldPrune(MoveValuePair& t_value, MoveValuePair& t_best, AlphaBeta& t_ab, bool isMinimizer);

	/// <summary>
	/// Given a gameboard, determine and return the legal moves.
	/// </summary>
	/// <param name="">Board to analyse</param>
	/// <param name="">A vector to add legal move indices to</param>
	void findValidMoves(Board, vector<uint8_t>&);

	/// <summary>
	/// Returns the minimum of two MoveValuePair's based on their value
	/// </summary>
	MoveValuePair& min(MoveValuePair& p1, MoveValuePair& p2)
	{
		return p1.second < p2.second
			? p1
			: p2;
	}

	/// <summary>
	/// Returns the maximum of two MoveValuePair's based on their value
	/// </summary>
	MoveValuePair& max(MoveValuePair& p1, MoveValuePair& p2)
	{
		return p1.second > p2.second
			? p1
			: p2;
	}

	// An array of bitsets, each representing a winning line on the game board
	std::array<Board*, 76> _winningLines;

	enum class AIDifficulty
	{
		EASY = -1,
		MEDIUM = 0,
		HARD = 1
	} _aiDifficulty{ AIDifficulty::EASY };
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