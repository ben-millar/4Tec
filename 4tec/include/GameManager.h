#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>

#include <BoardManager.h>
#include <GameData.h>

class GameManager
{
public:
	static GameManager* const getInstance() {
		static GameManager* const instance = new GameManager();
		return instance;
	}

	GameManager(GameManager&) = delete;
	GameManager& operator=(GameManager&) = delete;

	bool makeMove(Move t_move);

	void resetGame();

	Board* getCurrentPlayerBoard() { return &_currentPlayerTokens; }
	Board* getGameBoard() { return &_gameBoard; }

private:
	GameManager() {}
	BoardManager _boardManager;
	Board _gameBoard, _currentPlayerTokens;
	Player _currentPlayer{ Player::YELLOW };
	bool _gameOver{ false };

	void swapPlayers();
};

#endif