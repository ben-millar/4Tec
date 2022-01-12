#include <GameManager.h>

GameManager::GameManager() {}

////////////////////////////////////////////////////////////

bool GameManager::makeMove(Move t_move)
{
	if (_gameOver) return false;

	if (_boardManager.isValid(_gameBoard, t_move))
	{
		// Commit the move to our player's pieces
		_boardManager.makeMove(_currentPlayerTokens, t_move);

		// Commit the player's move to the board
		_gameBoard |= _currentPlayerTokens;

		_tokenManager.placePiece(t_move, _currentPlayer);

		Board winningLine;

		// Check if that was a winning move for the current player
		if (_boardManager.checkForWin(_currentPlayerTokens, winningLine))
		{
			(Player::RED == _currentPlayer)
				? std::cout << "Red player wins!" << std::endl
				: std::cout << "Yellow player wins!" << std::endl;

			array<uint8_t, 4> winningIndices;

			for (uint8_t i = 0, j = 0; i < winningLine.size(); ++i)
				if (winningLine.test(i)) winningIndices.at(j++) = i;

			_tokenManager.highlightWin(winningIndices, _currentPlayer);

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
	_tokenManager.reset();
	_gameOver = false;
}

////////////////////////////////////////////////////////////

void GameManager::swapPlayers()
{
	_currentPlayerTokens ^= _gameBoard;
	_currentPlayer = (Player::YELLOW == _currentPlayer)
		? Player::RED
		: Player::YELLOW;
}
