#include <TokenManager.h>

void TokenManager::loadTextures()
{
	m_manager = TextureManager::getInstance();
	m_manager->loadTexture("red","assets/images/redToken.png");
	m_manager->loadTexture("yellow","assets/images/yellowToken.png");
	for (auto& t : m_boardRender)
	{
		t.create(WINDOW_WIDTH, WINDOW_HEIGHT);
		t.clear(sf::Color::Transparent);
	}
}

///////////////////////////////////////////////////////////////////////////////

void TokenManager::placePiece(uint8_t t_layer, uint8_t t_row, uint8_t t_col)
{
	m_boardRender[4].clear(sf::Color::Transparent);
	sf::Vector2u tx = 
		m_manager->getTexture("board")->getSize();

	float layerWidth = tx.y / 4.0f;
	static std::array<sf::Vector2i, 16> points{ {
		{220,25}, {370,25}, {530,25}, {685,25},
		{195,70}, {365,70}, {530,70}, {700,70},
		{170, 125}, {350,125}, {535,125}, {725,125},
		{130,195}, {340,195}, {540,195}, {750,195}
	}};

	// .55, .6, .78, 1
	static std::array<float, 4> spriteScale{ .68f,.79f,.89f,1 };

	unsigned index = 4 * t_row + t_col;
	sf::Sprite r;
	const char* tex = (m_red) ? "red" : "yellow";
	r.setTexture(*m_manager->getTexture(tex));
	sf::Vector2u texSize = r.getTexture()->getSize();
	r.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	r.setScale(spriteScale[t_row], spriteScale[t_row]);
	m_red = !m_red;

	int pos = t_col;
	r.setPosition(points[index].x, points[index].y + (layerWidth * t_layer));

	m_boardRender[t_row].draw(r);
	m_boardRender[t_row].display();

	sf::Sprite s;
	for (int i = 0; i < 4; ++i)
	{
		s.setTexture(m_boardRender[i].getTexture());
		m_boardRender[4].draw(s);
	}

	m_boardRender[4].display();

	m_board.setTexture(m_boardRender[4].getTexture());
}
