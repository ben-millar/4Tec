#include <Game.h>

void Game::run()
{
	m_window = createWindow("AI | 4Tec");
	m_window->setKeyRepeatEnabled(false);

	loadFont();

	m_currentScreen = new MainMenu(this, &Game::setupGame, m_robotoTTF);
	m_currentScreen->addWindow(m_window);

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
}

////////////////////////////////////////////////////////////

void Game::processEvents()
{
	sf::Event e;
	while (m_window->pollEvent(e))
	{
		m_currentScreen->processEvents(e);
		if (e.type == sf::Event::Closed)
			m_window->close();
	}
}

////////////////////////////////////////////////////////////

void Game::update(sf::Time t_dTime)
{
}

////////////////////////////////////////////////////////////

void Game::render()
{
	m_currentScreen->render();
}

///////////////////////////////////////////////////////////////////////////////

void Game::setupGame(GameType t_type)
{
	delete m_currentScreen;
	m_currentScreen = new Gameplay();
	m_currentScreen->addWindow(m_window);
	static_cast<Gameplay*>(m_currentScreen)->loadGame(t_type);
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