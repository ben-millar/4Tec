#ifndef AI_INCLUDE
#define AI_INCLUDE

#include <Observer.h>
#include <Minimax.h>
#include <GameManager.h>

class AI : public Observer
{
public:
	/// <summary>
	/// Default Constructor for the AI 
	/// Defaults the player type to RED
	/// </summary>
	AI() : AI(Player::RED) {};
	AI(Player t_type) : m_type(t_type) { _gm = GameManager::getInstance(); };

	/// <summary>
	/// Allow the program to overwrite the type the AI uses
	/// </summary>
	/// <param name="t_type"> new type for the AI </param>
	void setType(Player t_type) { m_type = t_type; }

	/// <summary>
	/// Notify the AI that a move has been made 
	/// so it generates a move of its own
	/// </summary>
	void onNotify(Move t_move, Player t_player)override
	{
		Board* b = _gm->getGameBoard();
		Board* p = _gm->getCurrentPlayerBoard();

		Move AIMove = Minimax::getInstance()->findMove(b, p);
		_gm->onNotify(AIMove, m_type);
	};



protected:
	Player m_type;
	GameManager* _gm;
};
#endif