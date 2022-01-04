#ifndef PLAYER_INPUT_INCLUDE
#define PLAYER_INPUT_INCLUDE

#include <Subject.h>
#include <TextureManager.h>
#include <array>
#include <SFML/System/Vector2.hpp>

class PlayerInput : public Subject
{
public:
	PlayerInput() = default;

	void setType(Player t_type){ m_type = t_type;}

	void Click(sf::Vector2i t_mouseClick);

protected:
	Move calculateBoardPiece(sf::Vector2i t_mousePos);
	uint8_t getRow(float t_rowPct);
	Player m_type{ Player::YELLOW };
};
#endif