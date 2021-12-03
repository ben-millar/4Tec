 #include <Game.h>

void Game::run()
{
	m_window = createWindow("AI | 4Tec");
	m_window->setKeyRepeatEnabled(false);

	loadFont();
	loadTextures();

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
	m_boardTexture.loadFromFile("assets/images/board2.png");
	m_boardSprite.setTexture(m_boardTexture);
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
		//194
		else if (e.type == sf::Event::MouseButtonPressed)
		{
			auto points = calculateBoardPiece(sf::Mouse::getPosition(*m_window));
			std::cout << m_board.makeMove(std::get<0>(points), std::get<1>(points), std::get<2>(points));
			//std::cout << std::get<0>(points) << ", " << std::get<1>(points) << ", " << std::get<2>(points) << std::endl;
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

	m_window->draw(m_boardSprite);
	m_window->draw(m_text);

	m_window->display();
}

std::tuple<int, int, int> Game::calculateBoardPiece(sf::Vector2i t_mousePos)
{
	std::tuple<int, int, int> points(-1,-1,-1);
	/// <summary>
	/// variable used later
	/// </summary>
	int maxWidth = 720; 
	float minWidthScaler = 1.85f;
	float level = t_mousePos.y / 200.0f; // get the level the click is on 0-3
	float levelPct = level - (int)level; // remove the level to get in range 0-1
	float xOffset = 125 - (125 * levelPct); //change the offset of the x depending on how low in the level the click is
	float width = (maxWidth - xOffset * minWidthScaler); // how wide the board is at a given y value
	

	
	if (t_mousePos.x > xOffset && t_mousePos.x < xOffset + width) // check if the click is within the range width wise
		std::get<2>(points) = static_cast<int>((t_mousePos.x - xOffset) / (width / 4)); // store the info
	std::get<0>(points) = (int)level; // store the level as an int
	return points;
}

////////////////////////////////////////////////////////////

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title);
}
