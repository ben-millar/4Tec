#ifndef TOKEN_MANAGER_INCLUDE
#define TOKEN_MANAGER_INCLUDE

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <Globals.h>
#include <array>

#include <GameData.h>
#include <TextureManager.h>

class TokenManager
{
public:
	TokenManager() = default;
	~TokenManager() = default;

	void loadTextures();

	void placePiece(Move t_move);

	void reset();

	sf::Sprite& getSprite() { return m_board; }

private:
	TextureManager* m_manager;
	std::array<sf::RenderTexture, 5> m_boardRender;
	sf::Sprite m_board;
	bool m_red{ false };
};

#endif