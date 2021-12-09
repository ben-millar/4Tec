#include <TokenManager.h>

void TokenManager::loadTextures()
{
	m_redTexture.loadFromFile("assets/images/redToken.png");
	m_yellowTexture.loadFromFile("assets/images/yellowToken.png");
	m_boardRender.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_boardRender.clear(sf::Color::Transparent);
}

////////////////////////////////////////////////////////////

void TokenManager::placePiece(uint8_t t_layer, uint8_t t_row, uint8_t t_col)
{
	sf::Vector2u tx = 
		TextureManager::getInstance()->getTexture("board")->getSize();

	float layerWidth = tx.y / 4.0f;
	static std::array<sf::Vector2i, 16> points{ {
		{220,25}, {370,25}, {530,25}, {685,25},
		{195,70}, {365,70}, {530,70}, {700,70},
		{170, 125}, {350,125}, {535,125}, {725,125},
		{130,195}, {340,195}, {540,195}, {750,195}
	}};

	static std::array<float, 4> spriteScale{ .55f,.6f,.78f,1 };

	unsigned index = 4 * t_row + t_col;
	sf::Sprite r;
	r.setTexture((m_red) ? m_redTexture : m_yellowTexture);
	sf::Vector2u texSize = r.getTexture()->getSize();
	r.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	r.setScale(spriteScale[t_row], spriteScale[t_row]);
	m_red = !m_red;

	int pos = t_col;
	r.setPosition(points[index].x, points[index].y + (layerWidth * t_layer));

	m_boardRender.draw(r);
	m_boardRender.display();

	m_board.setTexture(m_boardRender.getTexture());
}
