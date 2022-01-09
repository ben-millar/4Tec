#include <GameManager.h>

bool GameManager::makeMove(Move t_move)
{
	if (_gameOver) return false;

	if (_boardManager.isValid(_gameBoard, t_move))
	{
		// Commit the move to our player's pieces
		_boardManager.makeMove(_currentPlayerTokens, t_move);

		// Commit the player's move to the board
		_gameBoard |= _currentPlayerTokens;

		// Check if that was a winning move for the current player
		if (_boardManager.checkForWin(_currentPlayerTokens))
		{
			(Player::RED == _currentPlayer)
				? std::cout << "Red player wins!" << std::endl
				: std::cout << "Yellow player wins!" << std::endl;

			_gameOver = true;
		}
		
		swapPlayers();

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////

void GameManager::resetGame()
{
	_gameBoard.reset();
	_currentPlayerTokens.reset();
	_tokens->reset();
	_gameOver = false;
}

void GameManager::onNotify(Move t_move, Player t_player)
{
	if (_gameOver) return;

	if (_boardManager.isValid(_gameBoard, t_move) && t_player == _currentPlayer)
	{
		// Commit the move to our player's pieces
		_boardManager.makeMove(_currentPlayerTokens, t_move);

		// Commit the player's move to the board
		_gameBoard |= _currentPlayerTokens;

		// Check if that was a winning move for the current player
		if (_boardManager.checkForWin(_currentPlayerTokens))
		{
			(Player::RED == _currentPlayer)
				? std::cout << "Red player wins!" << std::endl
				: std::cout << "Yellow player wins!" << std::endl;

			_gameOver = true;
		}
		_tokens->placePiece(t_move);

		swapPlayers();
	}
}

////////////////////////////////////////////////////////////

void GameManager::swapPlayers()
{
	_currentPlayerTokens ^= _gameBoard;
	_currentPlayer = (Player::YELLOW == _currentPlayer)
		? Player::RED
		: Player::YELLOW;
}
