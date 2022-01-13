#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <bitset>
#include <cstdint>
#include <tuple>

using Board = std::bitset<4 * 4 * 4>;
using Move = std::tuple<uint8_t, uint8_t, uint8_t>;

const Move NULL_MOVE = Move{ -1,-1,-1 };

enum class GameType
{
	LOCAL,
	ONLINE,
	AI,
	AIvAI
};

enum class AIDifficulty
{
	NONE = -2,
	EASY = -1,
	MEDIUM = 0,
	HARD = 1
};

enum class NetworkType
{
	NONE=-1,
	HOST=0,
	CLIENT=1
};

enum class Player : uint8_t
{
	RED,
	YELLOW
};

#endif