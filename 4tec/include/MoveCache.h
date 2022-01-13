#ifndef MOVE_CACHE_H
#define MOVE_CACHE_H

#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <string>

#include <GameData.h>

using namespace std;

class MoveCache
{
public:
	/// <summary>
	/// Inserts a new board/evaluation pair into our map. If a key already exists,
	/// it's value is overwritten by the new value. If the cache is at max capacity,
	/// the oldest element is removed to make room for the passed element.
	/// </summary>
	/// <param name="t_board">Board which was evaluated</param>
	/// <param name="t_playerTokens">Board containing the current players pieces</param>
	/// <param name="t_move">Board which contains the move to be made</param>
	/// <param name="t_eval">Evaluation of the board</param>
	void add(Board const& t_board, Board const& t_playerTokens, Board const& t_move, int t_eval);

	/// <summary>
	/// Returns the evaluation of a given board if it exists in the map.
	/// </summary>
	/// <param name="t_board">Board to return evaluation for</param>
	/// <param name="t_playerTokens">Board containing the current players pieces</param>
	/// <param name="t_move">Board which contains the move to be made</param>
	/// <returns>Value of board if in map, otherwise -1</returns>
	int find(Board const& t_board, Board const& t_playerTokens, Board const& t_move);

	/// <summary>
	/// Clears the movecache
	/// </summary>
	void clear();

private:
	// Boards that have been evaluated previously are stored here
	unordered_map<string, int> _lookupTable;

	// This queue tracks items added to the lookup table, and
	// allows us to remove the oldest when the table hits capacity
	queue<string> _activeDataQueue;

	// Number of board evaluations to store in our lookup table
	const unsigned MAX_CACHE_SIZE{ 1000u };
};

#endif