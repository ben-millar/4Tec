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

	enum class Type
	{
		RED,
		YELLOW
	};

	TokenManager();
	~TokenManager() = default;

	void placePiece(Move t_move, Player t_player, bool t_highlight = false);

	void highlightWin(array<uint8_t, 4> t_win, Player t_player);

	void reset();

	sf::Sprite& getSprite() { return m_board; }

private:
	void loadTextures();

	Board m_yellowTokens, m_redTokens;
	array<sf::Vector2f, 64> m_positions;

	TextureManager* m_manager;
	std::array<sf::RenderTexture, 5> m_boardRender;
	sf::Sprite m_board;
};

#endif