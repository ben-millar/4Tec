#include <Game.h>

void Game::run()
{
	m_window = createWindow("AI | 4Tec");
	m_window->setKeyRepeatEnabled(false);

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
	if (WINDOW_HEIGHT < 780)
		tm->loadTexture("board", "assets/images/board_small.png");
	else if (WINDOW_HEIGHT < 975)
		tm->loadTexture("board", "assets/images/board_medium.png");
	else
		tm->loadTexture("board", "assets/images/board_large.png");

	m_boardSprite.setTexture(*tm->getTexture("board"));

	m_tokens.loadTextures();
}

////////////////////////////////////////////////////////////

void Game::loadShader()
{
	m_shader.loadFromFile("assets/shader/vertShader.txt", "assets/shader/fragShader.txt");

	m_shader.setUniform("windowHeight", (float)WINDOW_HEIGHT);

	m_shader.setUniform("texture", sf::Shader::CurrentTexture);
	m_shader.setUniform("tableWidth", (float)(TextureManager::getInstance()->getTexture("board")->getSize().x));
	float h = (float)TextureManager::getInstance()->getTexture("board")->getSize().y;
	float wh = (float)WINDOW_HEIGHT;
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
			default:
				break;
			}
		else if (e.type == sf::Event::MouseButtonPressed)
		{
			auto input = Input::calculateBoardPiece(sf::Mouse::getPosition(*m_window));
			uint8_t layer, row, col;
			tie(layer, row, col) = input;

			//cout << (int)(layer) << ", " << (int)(row) << ", " << (int)(col) << endl;
			if (m_board.makeMove(layer, row, col))
				m_tokens.placePiece(layer, row, col);
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
	m_window->draw(m_tokens, &m_shader);
	//m_window->draw(m_shadowSprite);

	m_window->display();
}

///////////////////////////////////////////////////////////////////////////////

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title, sf::Style::Titlebar | sf::Style::Close);
}
