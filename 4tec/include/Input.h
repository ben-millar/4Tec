#ifndef INPUT_INCLUDE
#define INPUT_INCLUDE

#include <array>
#include <cstdint>
#include <tuple>

#include <SFML/System/Vector2.hpp>

#include <TextureManager.h>

class Input
{
public:
	static std::tuple<uint8_t, uint8_t, uint8_t> calculateBoardPiece(sf::Vector2i t_mousePos);
private:
	static uint8_t getRow(float t_rowPct);
};

#endif