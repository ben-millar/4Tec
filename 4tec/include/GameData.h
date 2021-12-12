#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <bitset>
#include <cstdint>
#include <tuple>

using Board = std::bitset<4 * 5 * 5>;
using Move = std::tuple<uint8_t, uint8_t, uint8_t>;

enum class Player : uint8_t
{
	RED,
	YELLOW
};

#endif