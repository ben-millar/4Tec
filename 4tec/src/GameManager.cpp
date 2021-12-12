#include <GameManager.h>

bool GameManager::makeMove(Move t_move)
{
	if (_boardManager.isValid(_gameBoard, t_move))
	{
		// Commit the move to our player's pieces
		_boardManager.makeMove(_currentPlayerTokens, t_move);

		// Commit the player's move to the board
		_gameBoard |= _currentPlayerTokens;

		// Check if that was a winning move for the current player
		if (_boardManager.checkForWin(_currentPlayerTokens))
		{
			std::cout << "Winner!" << std::endl;
		}
		
		swapPlayers();

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////

void GameManager::swapPlayers()
{
	_currentPlayerTokens ^= _gameBoard;
	_currentPlayer = (Player::YELLOW == _currentPlayer)
		? Player::RED
		: Player::YELLOW;
}