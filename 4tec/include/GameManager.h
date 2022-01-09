#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>
#include <BoardManager.h>
#include <GameData.h>
#include <Observer.h>
#include <TokenManager.h>

class GameManager : public Observer
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

	void onNotify(Move t_move, Player t_player);

	void swapPlayers();
private:
	GameManager() { m_tokens = TokenManager::getInstance(); }
	BoardManager _boardManager;
	Board _gameBoard, _currentPlayerTokens;
	Player _currentPlayer{ Player::YELLOW };
	bool _gameOver{ false };
	TokenManager* m_tokens;

};

#endif