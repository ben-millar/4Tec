#include <Game.h>

void Game::run()
{
	m_window = createWindow("AI | 4Tec");
	m_window->setKeyRepeatEnabled(false);

	loadFont();
	loadTextures();
	loadShader();

	_gm = GameManager::getInstance();

	if (GameType::ONLINE == _gameType)
	{
		_network = new Network();

		if (NetworkType::CLIENT == _networkType)
		{
			_network->client("149.153.106.163", 420);

			render(); // Sneak in a draw call while we wait for the host

			Move m = _network->tryRecv();
			_gm->makeMove(m);
		}
		else
			_network->host("149.153.106.163", 420);
	}

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
	if (SCREEN_HEIGHT < 780)
		tm->loadTexture("board", "assets/images/board_small.png");
	else if (SCREEN_HEIGHT < 975)
		tm->loadTexture("board", "assets/images/board_medium.png");
	else
		tm->loadTexture("board", "assets/images/board_large.png");

	m_boardSprite.setTexture(*tm->getTexture("board"));
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
				if (GameType::ONLINE != _gameType)
					_gm->resetGame();
				break;
			default:
				break;
			}
		else if (e.type == sf::Event::MouseButtonPressed)
		{
			Move move = Input::calculateBoardPiece(sf::Mouse::getPosition(*m_window));

			if (_gm->makeMove(move))
			{
				render(); // Sneak in a draw call while we wait for next move

				if (GameType::AI == _gameType)
				{
					Board* b = _gm->getGameBoard();
					Board* p = _gm->getCurrentPlayerBoard();

					Move AIMove = Minimax::getInstance()->findMove(b, p);

					_gm->makeMove(AIMove);
				}
				else if (GameType::LOCAL == _gameType)
				{
					// Do nothing
				}
				else if (GameType::ONLINE == _gameType)
				{
					_network->trySend(move);

					Move m = _network->tryRecv();
					_gm->makeMove(m);
				}
				else if (GameType::AIvAI == _gameType)
				{
					while (true)
					{
						Board* b = _gm->getGameBoard();
						Board* p = _gm->getCurrentPlayerBoard();

						Move AIMove = Minimax::getInstance()->findMove(b, p);

						if (!_gm->makeMove(AIMove))
							break;

						render();
					}
				}
			}
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
	m_window->draw(_gm->getTokenSprite(), &m_shader);

	m_window->display();
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
