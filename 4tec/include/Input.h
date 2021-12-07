#ifndef INPUT_INCLUDE
#define INPUT_INCLUDE

#include <tuple>
#include <SFML/System/Vector2.hpp>
#include <Board.h>

class Input
{
public:
	Input() = default;
	bool handleMouseInput(sf::Vector2i t_mousePos);

	void assignBoard(Board* t_board);

private:
	std::tuple<uint8_t, uint8_t, uint8_t> calculateBoardPiece(sf::Vector2i t_mousePos);
	uint8_t getRow(float t_levelPct);
	Board* m_board;
};

#endif