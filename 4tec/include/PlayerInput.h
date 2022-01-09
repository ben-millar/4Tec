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

	/// <summary>
	/// Allows the program to overwrite what type of input the player sends
	/// </summary>
	/// <param name="t_type"></param>
	void setType(Player t_type){ m_type = t_type;}

	/// <summary>
	/// Generates a move based on where the user clicked and sends the move to any observers
	/// </summary>
	/// <param name="t_mouseClick"> Where the user clicked </param>
	void GenerateMove(sf::Vector2i t_mouseClick);

	/// <summary>
	/// Adds a network to the input so the when a move is made it gets sent across
	/// </summary>
	/// <param name="t_network"> Network to send to </param>
	void addNetwork(Network* t_network) { m_network = t_network; }

protected:
	/// <summary>
	/// converts from mouse click to cell on the board
	/// </summary>
	/// <param name="t_mousePos"> Where the user clicked </param>
	/// <returns> The level, row and col located at the click </returns>
	Move calculateBoardPiece(sf::Vector2i t_mousePos);

	/// <summary>
	/// Gets what row was clicked on based on a percentage
	/// </summary>
	/// <param name="t_rowPct"> percentage from the top of the level </param>
	/// <returns> What row it belongs to </returns>
	uint8_t getRow(float t_rowPct);

	Player m_type{ Player::YELLOW };
	Network* m_network;
};
#endif