#include <MainMenu.h>

MainMenu::MainMenu(Game* t_game, std::function<void(Game*, GameType, NetworkType, AIDifficulty)> t_func, sf::Font& t_font) :
	m_gameCaller(t_game),
	m_launchGame(t_func),
	m_background(sf::Quads),
	m_gameFont(t_font)
{
	sf::Vector2f windowSize;
	if (SCREEN_HEIGHT < 780u)
		windowSize = { 531.0f, 585.0f };
	else if (SCREEN_HEIGHT < 975u)
		windowSize = { 708.0f, 780.0f };
	else
		windowSize = { 885.0f, 975.0f };
}

////////////////////////////////////////////////////////////

MainMenu::~MainMenu()
{
	for (auto& btn : m_AI)
		delete btn;
	for (auto& btn : m_local)
		delete btn;
	for (auto& btn : m_network)
		delete btn;
	for (auto& btn : m_options)
		delete btn;
}

////////////////////////////////////////////////////////////

void MainMenu::processEvents(sf::Event& t_event, sf::RenderWindow* t_window)
{
	if (t_event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*t_window));

		if (m_tabButton)
			if (!m_tabButton->getSprite().getGlobalBounds().contains(pos))
			{
				m_tabButton->loseFocus();
				m_tabButton = nullptr;
			}
			

		for (auto& btn : m_options)
		{
			if (btn->getSprite().getGlobalBounds().contains(pos))
				if (m_currentButton != btn)
				{
					if (m_currentButton)
						m_currentButton->loseFocus();
					m_currentButton = btn;
					m_currentButton->activate();
				}
		}
		if (m_currentTab)
		{
			for (auto& btn : *m_currentTab)
			{
				if (btn->getSprite().getGlobalBounds().contains(pos))
					if (m_tabButton != btn)
					{
						if (m_tabButton)
							m_tabButton->loseFocus();
						m_tabButton = btn;
						m_tabButton->gainFocus();
					}
			}
		}
	}
	else if (t_event.type == sf::Event::MouseButtonReleased)
	{
		if (m_currentTab)
			if (m_tabButton)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(*t_window);
				if (m_tabButton->getSprite().getGlobalBounds().contains((sf::Vector2f)pos))
					m_tabButton->activate();
			}
	}
}

////////////////////////////////////////////////////////////

void MainMenu::render(sf::RenderWindow* t_window)
{
	t_window->clear(sf::Color(50U, 50U, 50U, 255U));
	for (auto& btn : m_options)
		btn->render(t_window);

	t_window->draw(m_background);

	if (m_currentTab)
		for (auto& btn : *m_currentTab)
			btn->render(t_window);

	t_window->display();
}

////////////////////////////////////////////////////////////

void MainMenu::initOptions(sf::Font& t_font, sf::Vector2f t_windowSize)
{
}

////////////////////////////////////////////////////////////

void MainMenu::showAITab()
{
	m_currentTab = &m_AI;
	if (m_tabButton)
		m_tabButton->loseFocus();
	m_tabButton = nullptr;
}

////////////////////////////////////////////////////////////

void MainMenu::showLocalTab()
{
	m_currentTab = &m_local;
	if (m_tabButton)
		m_tabButton->loseFocus();
	m_tabButton = nullptr;
}

////////////////////////////////////////////////////////////

void MainMenu::showNetworkTab()
{
	m_currentTab = &m_network;
	if (m_tabButton)
		m_tabButton->loseFocus();
	m_tabButton = nullptr;
}

////////////////////////////////////////////////////////////

Button* MainMenu::createButton(std::string t_name, GameType t_gt, NetworkType t_nt, AIDifficulty t_ai, sf::Vector2f t_pos)
{
	Button* btn = new Button(m_gameFont, t_name);
	btn->addFunction(m_gameCaller, m_launchGame, t_gt, t_nt, t_ai);
	return nullptr;
}
