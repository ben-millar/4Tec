#ifndef INPUT_MANAGER_INCLUDE
#define INPUT_MANAGER_INCLUDE

#include <Observer.h>
#include <GameManager.h>
#include <TokenManager.h>
#include <shared_mutex>

class InputManager : public Observer
{
public:
	static InputManager* const getInstance() {
		static InputManager* const instance = new InputManager();
		return instance;
	}

	InputManager(InputManager&) = delete;
	InputManager& operator=(InputManager&) = delete;

	/// <summary>
	/// Handles the moves that happen during the game.
	/// as multiple move requests can be send this function
	/// makes sure that the players on make the move when it is
	/// their turn.
	/// </summary>
	/// <param name="t_move"> The move that was played </param>
	/// <param name="t_player"> The player that made the move </param>
	void onNotify(Move t_move, Player t_player)override
	{
		if (t_player == m_turn && validateMove(t_move))
		{
			m_game->makeMove(t_move);
			m_turn = (m_turn == Player::YELLOW)
				? Player::RED 
				: Player::YELLOW;
			m_tokens->placePiece(t_move);
		}
	}

	GameManager* getGameManager() { return m_game; }

	void toggleTurn()
	{
		m_turn = (m_turn == Player::YELLOW)
			? Player::RED
			: Player::YELLOW;
	}

	std::shared_mutex m_mutex;
private:

	bool validateMove(Move t_move)
	{
		uint8_t layer, row, col;
		std::tie(layer, row, col) = t_move;
		return (layer < 9 && row < 9 && col < 9);
	}


	InputManager() : m_turn(Player::YELLOW) 
	{
		m_game = GameManager::getInstance();
		m_tokens = TokenManager::getInstance();
	}
	GameManager* m_game;
	TokenManager* m_tokens;
	Player m_turn;
};

#endif