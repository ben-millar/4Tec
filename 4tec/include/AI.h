#ifndef AI_INCLUDE
#define AI_INCLUDE

#include <Observer.h>
#include <InputManager.h>
#include <Minimax.h>

class AI : public Observer
{
public:
	AI() : AI(Player::RED) {};
	AI(Player t_type) : m_type(t_type) { m_manager = InputManager::getInstance(); };

	void setType(Player t_type) { m_type = t_type; }

	void onNotify(Move t_move, Player t_player)override
	{
		Board* b = m_manager->getGameManager()->getGameBoard();
		Board* p = m_manager->getGameManager()->getCurrentPlayerBoard();

		Move AIMove = Minimax::getInstance()->findMove(b, p);
		m_manager->onNotify(AIMove, m_type);
	};



protected:
	Player m_type;
	InputManager* m_manager;
};
#endif