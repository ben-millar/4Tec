#ifndef TOKEN_MANAGER_INCLUDE
#define TOKEN_MANAGER_INCLUDE

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <Globals.h>
#include <array>

class TokenManager
{
public:
	TokenManager() = default;
	~TokenManager() = default;

	void loadTextures();

	void placePiece(std::tuple<uint8_t, uint8_t, uint8_t> t_positon);

	operator sf::Drawable& () { return m_board; }
private:
	sf::Texture m_redTexture;
	sf::Texture m_yellowTexture;
	sf::RenderTexture m_boardRender;
	sf::Sprite m_board;
	bool m_red{ false };
};

#endif