#include <TokenManager.h>

void TokenManager::loadTextures()
{
	m_redTexture.loadFromFile("assets/images/redToken.png");
	m_yellowTexture.loadFromFile("assets/images/yellowToken.png");
	m_boardRender.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_boardRender.clear(sf::Color::Transparent);
}

////////////////////////////////////////////////////////////

void TokenManager::placePiece(std::tuple<uint8_t, uint8_t, uint8_t> t_positon)
{
	static std::array<sf::Vector2f, 3> positions
	{
		sf::Vector2f{0,0},
		{100,0},
		{200,0} 
	};
	static sf::Sprite r;
	r.setTexture((m_red) ? m_redTexture : m_yellowTexture);
	m_red = !m_red;

	int pos = std::get<2>(t_positon);
	r.setPosition(positions[pos]);

	m_boardRender.draw(r);
	m_boardRender.display();

	m_board.setTexture(m_boardRender.getTexture());
}
