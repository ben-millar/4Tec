#ifndef INPUT_INCLUDE
#define INPUT_INCLUDE

#include <tuple>
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <array>

class Input
{
public:
	static std::tuple<uint8_t, uint8_t, uint8_t> calculateBoardPiece(sf::Vector2i t_mousePos);
private:
	static uint8_t getRow(float t_levelPct);
};

#endif