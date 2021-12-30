#include <TokenManager.h>

void TokenManager::loadTextures()
{
	m_manager = TextureManager::getInstance();
	m_manager->loadTexture("red","assets/images/redToken.png");
	m_manager->loadTexture("yellow","assets/images/yellowToken.png");
	for (auto& t : m_boardRender)
	{
		t.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		t.clear(sf::Color::Transparent);
	}
}

///////////////////////////////////////////////////////////////////////////////

void TokenManager::placePiece(Move t_move)
{
	uint8_t layer, row, col;
	std::tie(layer, row, col) = t_move;

	m_boardRender[4].clear(sf::Color::Transparent);
	sf::Vector2u tx = 
		m_manager->getTexture("board")->getSize();

	float layerWidth = tx.y / 4.0f;
	static std::array<float, 4> heights{ .104f, .29f, .521f, .8125f };

	static std::array<float, 16> widths{
		.248f, .428f, .598f, .774f,
		.220f, .412f, .598f, .79f,
		.192f, .395f, .604f, .819f,
		.146f, .384f, .610f, .847f
	};

	// .55, .6, .78, 1
	static std::array<float, 4> spriteScale{ .68f,.79f,.89f,1 };

	unsigned index = 4 * row + col;
	sf::Sprite r;
	const char* tex = (m_red) ? "red" : "yellow";
	r.setTexture(*m_manager->getTexture(tex));
	sf::Vector2u texSize = r.getTexture()->getSize();
	r.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	r.setScale(spriteScale[row], spriteScale[row]);
	m_red = !m_red;

	int pos = col;
	r.setPosition(tx.x * widths[index], layerWidth * heights[index / 4] + (layerWidth * layer));

	m_boardRender[row].draw(r);
	m_boardRender[row].display();

	sf::Sprite s;
	for (int i = 0; i < 4; ++i)
	{
		s.setTexture(m_boardRender[i].getTexture());
		m_boardRender[4].draw(s);
	}

	m_boardRender[4].display();

	m_board.setTexture(m_boardRender[4].getTexture());
}

///////////////////////////////////////////////////////////////////////////////

void TokenManager::reset()
{
	for (auto& b : m_boardRender)
		b.clear(sf::Color::Transparent);
	m_board.setTexture(m_boardRender[4].getTexture());
}
