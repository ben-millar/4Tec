#include <Gameplay.h>

Gameplay::Gameplay()
{
	_gm = GameManager::getInstance();
	_tm = TokenManager::getInstance();
}

////////////////////////////////////////////////////////////

void Gameplay::loadGame(GameType t_type)
{
	loadTextures();
	loadShader();

	switch (t_type)
	{
	case GameType::EASY:
	case GameType::MEDIUM:
	case GameType::HARD:
		m_ai = new AI();
		m_player.addObserver(m_ai);
		break;
	case GameType::CLIENT:
		m_network = new Network();
		m_network->client("192.168.8.148", 420);
		m_network->addObserver(_gm);
		m_player.addNetwork(m_network);
		_gm->swapPlayers();
		break;
	case GameType::HOST:
		m_network = new Network();
		m_network->host("192.168.8.148", 420);
		m_network->addObserver(_gm);
		m_player.addNetwork(m_network);
		break;
	case GameType::LOCAL:

		break;
	}
	m_player.addObserver(_gm);
}

////////////////////////////////////////////////////////////

void Gameplay::processEvents(sf::Event& t_event)
{
	if (t_event.type == sf::Event::KeyPressed)
	{
		switch (t_event.key.code)
		{
		case sf::Keyboard::R:
			_gm->resetGame();
			break;
		}
	}
	else if (t_event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
		m_player.GenerateMove(mousePos);
	}
}

////////////////////////////////////////////////////////////

void Gameplay::render()
{
	m_window->clear();

	m_window->draw(m_boardSprite,&m_shader);
	m_window->draw(*_tm, &m_shader);

	m_window->display();
}

////////////////////////////////////////////////////////////

void Gameplay::loadTextures()
{
	TextureManager* tm = TextureManager::getInstance();
	TokenManager* tokens = TokenManager::getInstance();
	tokens->loadTextures();
	
	if (SCREEN_HEIGHT < 780)
		tm->loadTexture("board", "assets/images/board_small.png");
	else if (SCREEN_HEIGHT < 975)
		tm->loadTexture("board", "assets/images/board_medium.png");
	else
		tm->loadTexture("board", "assets/images/board_large.png");

	m_boardSprite.setTexture(*tm->getTexture("board"));
}

////////////////////////////////////////////////////////////

void Gameplay::loadShader()
{
	m_shader.loadFromFile("assets/shader/vertShader.txt", "assets/shader/fragShader.txt");

	m_shader.setUniform("windowHeight", (float)m_window->getSize().y);

	m_shader.setUniform("texture", sf::Shader::CurrentTexture);
	m_shader.setUniform("tableWidth", (float)(TextureManager::getInstance()->getTexture("board")->getSize().x));
	float h = (float)TextureManager::getInstance()->getTexture("board")->getSize().y;
	float wh = (float)m_window->getSize().y;
	m_shader.setUniform("relativeLayerHeight", h / wh / 4.0f);
}
