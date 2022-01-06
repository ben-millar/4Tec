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
	static TokenManager* const getInstance() {
		static TokenManager* const instance = new TokenManager();
		return instance;
	}

	TokenManager(TextureManager&) = delete;
	TokenManager& operator=(TokenManager&) = delete;

	void loadTextures();

	void placePiece(Move t_move);

	void reset();

	operator sf::Drawable&() { return m_board; }

private:
	TokenManager() = default;
	~TokenManager() = default;

	TextureManager* m_manager{nullptr};
	std::array<sf::RenderTexture, 5> m_boardRender;
	sf::Sprite m_board;
	bool m_red{ false };
};
#endif