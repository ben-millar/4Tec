#include <TokenManager.h>

TokenManager::TokenManager()
{
	loadTextures();

	sf::Vector2u boardSize =
		m_manager->getTexture("board")->getSize();

	static std::array<float, 4> heights{ .104f, .29f, .521f, .8125f };

	static std::array<float, 16> widths{
		.248f, .428f, .598f, .774f,
		.220f, .412f, .598f, .79f,
		.192f, .395f, .604f, .819f,
		.146f, .384f, .610f, .847f
	};

	for (int i = 0; i < m_positions.size(); ++i)
	{
		float layerHeight = boardSize.y / 4.f;
		int layer = i / 4;

		float xPos = boardSize.x * widths.at(i % 16);
		float yPos = layerHeight * (i / 16) + (layerHeight * heights.at(layer % 4));

		m_positions.at(i) = { xPos, yPos };
	}
}

///////////////////////////////////////////////////////////////////////////////

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

void TokenManager::placePiece(Move t_move, Player t_player, bool t_highlight)
{
	uint8_t layer, row, col;
	std::tie(layer, row, col) = t_move;

	uint8_t index = 16 * layer + 4 * row + col;

	m_boardRender[4].clear(sf::Color::Transparent);

	// .55, .6, .78, 1
	static std::array<float, 4> spriteScale{ .68f,.79f,.89f,1 };

	sf::Sprite r;
	const char* tex = (Player::RED == t_player) ? "red" : "yellow";
	r.setTexture(*m_manager->getTexture(tex));
	sf::Vector2u texSize = r.getTexture()->getSize();
	r.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	r.setScale(spriteScale[row], spriteScale[row]);

	if (t_highlight)
		r.setColor(sf::Color::Cyan);
	else
		r.setColor(
			(Player::RED == t_player)
			? sf::Color::Red
			: sf::Color::Yellow
		);

	int pos = col;
	r.setPosition(m_positions.at(index));

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

void TokenManager::highlightWin(array<uint8_t, 4> t_win, Player t_player)
{
	uint8_t layer, row, col;

	for (uint8_t& index : t_win)
	{
		layer = index / 16;
		row = (index - layer * 16) / 4;
		col = index - (layer * 16 + row * 4);

		placePiece(Move(layer, row, col), t_player, true);
	}	
}

///////////////////////////////////////////////////////////////////////////////

void TokenManager::reset()
{
	for (auto& b : m_boardRender)
		b.clear(sf::Color::Transparent);
	m_board.setTexture(m_boardRender[4].getTexture());
}
