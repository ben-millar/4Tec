#include <Game.h>

void Game::run()
{
	m_window = createWindow("AI | 4Tec");
	m_window->setKeyRepeatEnabled(false);

	_gm = GameManager::getInstance();
	m_tokens = TokenManager::getInstance();
	m_inputs = InputManager::getInstance();

	setupGame(GameType::LAN);

	loadFont();
	loadTextures();
	loadShader();

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.0f);

	while (m_window->isOpen())
	{
		sf::Time dT = clock.restart();
		lag += dT;

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		update(dT);
		render();
	}
	m_network.disconnect();
	m_network.~Network();
}

////////////////////////////////////////////////////////////

void Game::loadFont()
{
	m_robotoTTF.loadFromFile("assets/fonts/Roboto-Thin.ttf");

	// FOR TESTING PURPOSES
	//m_text.setFont(m_robotoTTF);
	//m_text.setCharacterSize(96U);
	//m_text.setString("[ESC] to close window");
	//m_text.setPosition({ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f });
}

////////////////////////////////////////////////////////////

void Game::loadTextures()
{
	TextureManager* tm = TextureManager::getInstance();
	if (SCREEN_HEIGHT < 780)
		tm->loadTexture("board", "assets/images/board_small.png");
	else if (SCREEN_HEIGHT < 975)
		tm->loadTexture("board", "assets/images/board_medium.png");
	else
		tm->loadTexture("board", "assets/images/board_large.png");

	m_boardSprite.setTexture(*tm->getTexture("board"));

	m_tokens->loadTextures();
}

////////////////////////////////////////////////////////////

void Game::loadShader()
{
	m_shader.loadFromFile("assets/shader/vertShader.txt", "assets/shader/fragShader.txt");

	m_shader.setUniform("windowHeight", (float)m_window->getSize().y);

	m_shader.setUniform("texture", sf::Shader::CurrentTexture);
	m_shader.setUniform("tableWidth", (float)(TextureManager::getInstance()->getTexture("board")->getSize().x));
	float h = (float)TextureManager::getInstance()->getTexture("board")->getSize().y;
	float wh = (float)m_window->getSize().y;
	m_shader.setUniform("relativeLayerHeight", h / wh / 4.0f);
}

////////////////////////////////////////////////////////////

void Game::processEvents()
{
	sf::Event e;
	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();
		else if (e.type == sf::Event::KeyPressed)
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				m_window->close();
				break;
			case sf::Keyboard::R:
				_gm->resetGame();
				m_tokens->reset();
				break;
			default:
				break;
			}
		else if (e.type == sf::Event::MouseButtonPressed)
		{
			if (m_player)
				m_player->Click(sf::Mouse::getPosition(*m_window));
		}
	}
}

////////////////////////////////////////////////////////////

void Game::update(sf::Time t_dTime)
{
}

////////////////////////////////////////////////////////////

void Game::render()
{
	m_window->clear(sf::Color::Black);

	m_window->draw(m_boardSprite, &m_shader);
	m_window->draw(m_text);
	m_window->draw(*m_tokens, &m_shader);

	m_window->display();
}

///////////////////////////////////////////////////////////////////////////////

void Game::setupGame(GameType t_type)
{
	switch (t_type)
	{
	case GameType::PVE:
		m_player = new PlayerInput();
		m_ai = new AI();
		m_player->addObserver(m_inputs);
		m_player->addObserver(m_ai);
		break;
	case GameType::AIvsAI:

		break;
	case GameType::PVP:
		m_player = new PlayerInput();
		m_network.client("192.168.8.148", 420);
		m_player->addObserver(m_inputs);
		m_network.addObserver(m_inputs);
		m_inputs->toggleTurn();
		m_network.trySend({ '1','1','1' });
		break;
	case GameType::LAN:
		m_player = new PlayerInput();
		m_network.host("192.168.8.148", 420);
		m_player->addObserver(m_inputs);
		m_network.addObserver(m_inputs);
		m_inputs->toggleTurn();
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	sf::Vector2u windowSize;
	if (SCREEN_HEIGHT < 780u)
		windowSize = { 531, 585 };
	else if (SCREEN_HEIGHT < 975u)
		windowSize = { 708, 780 };
	else
		windowSize = { 885, 975 };

	return new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), t_title, sf::Style::Titlebar | sf::Style::Close);
}
