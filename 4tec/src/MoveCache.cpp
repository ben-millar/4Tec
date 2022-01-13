#include "MoveCache.h"

void MoveCache::add(Board const& t_board, Board const& t_playerTokens, Board const& t_move, int t_eval)
{
	auto key = string(t_board.to_string() + t_playerTokens.to_string() + t_move.to_string());
	_activeDataQueue.push(key);

	if (_activeDataQueue.size() > MAX_CACHE_SIZE)
	{
		_lookupTable.erase(_activeDataQueue.front());
		_activeDataQueue.pop();
	}

	_lookupTable.insert_or_assign(key, t_eval);
}

////////////////////////////////////////////////////////////

int MoveCache::find(Board const& t_board, Board const& t_playerTokens, Board const& t_move)
{
	auto key = string(t_board.to_string() + t_playerTokens.to_string() + t_move.to_string());

	return _lookupTable.count(key)
		? _lookupTable.at(key)
		: -1;
}

////////////////////////////////////////////////////////////

void MoveCache::clear()
{
	_lookupTable.clear();

	while (!_activeDataQueue.empty())
		_activeDataQueue.pop();
}
