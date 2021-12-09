#ifndef TOKEN_MANAGER_INCLUDE
#define TOKEN_MANAGER_INCLUDE

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <Globals.h>
#include <array>

#include <TextureManager.h>

class TokenManager
{
public:
	TokenManager() = default;
	~TokenManager() = default;

	void loadTextures();

	void placePiece(uint8_t t_layer, uint8_t t_row, uint8_t t_col);

	operator sf::Drawable&() { return m_board; }
private:
	TextureManager* m_manager;
	std::array<sf::RenderTexture, 5> m_boardRender;
	sf::Sprite m_board;
	bool m_red{ false };
};

#endif