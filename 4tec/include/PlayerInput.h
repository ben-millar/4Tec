#ifndef PLAYER_INPUT_INCLUDE
#define PLAYER_INPUT_INCLUDE

#include <Subject.h>
#include <TextureManager.h>
#include <array>
#include <Network.h>
#include <SFML/System/Vector2.hpp>

class PlayerInput : public Subject
{
public:
	/// <summary>
	/// Constructor for the player input
	/// Player needs a reference to the network so it can try send the move over the internet
	/// </summary>
	/// <param name="t_nw"></param>
	PlayerInput() = default;

	void setType(Player t_type){ m_type = t_type;}

	void Click(sf::Vector2i t_mouseClick);

	void addNetwork(Network* t_network) { m_network = t_network; }

protected:
	Move calculateBoardPiece(sf::Vector2i t_mousePos);
	uint8_t getRow(float t_rowPct);
	Player m_type{ Player::YELLOW };
	Network* m_network;
};
#endif