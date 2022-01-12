#include <MainMenu.h>

MainMenu::MainMenu(Game* t_game, std::function<void(Game*, GameType)> t_func, sf::Font& t_font) :
	m_gameCaller(t_game),
	m_launchGame(t_func),
	m_background(sf::Quads)
{
	float offset = 10.0f;
	sf::Vector2f windowSize;
	if (SCREEN_HEIGHT < 780u)
		windowSize = { 531.0f, 585.0f };
	else if (SCREEN_HEIGHT < 975u)
		windowSize = { 708.0f, 780.0f };
	else
		windowSize = { 885.0f, 975.0f };

	m_background.append({ {windowSize.x / 2,offset}, sf::Color(150U,150U,150U,255U) });
	m_background.append({ {windowSize.x - offset,offset}, sf::Color(150U,150U,150U,255U) });
	m_background.append({ {windowSize.x - offset,windowSize.y - offset}, sf::Color(150U,150U,150U,255U) });
	m_background.append({ {windowSize.x / 2,windowSize.y - offset}, sf::Color(150U,150U,150U,255U) });

	initOptions(t_font, windowSize);
	initTabs(t_font, windowSize);
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

void MainMenu::processEvents(sf::Event& t_event)
{
	if (t_event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));

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
				sf::Vector2i pos = sf::Mouse::getPosition(*m_window);
				if (m_tabButton->getSprite().getGlobalBounds().contains((sf::Vector2f)pos))
					m_tabButton->activate();
			}
	}
}

////////////////////////////////////////////////////////////

void MainMenu::render()
{
	m_window->clear(sf::Color(50U, 50U, 50U, 255U));
	for (auto& btn : m_options)
		btn->render(m_window);

	m_window->draw(m_background);

	if (m_currentTab)
		for (auto& btn : *m_currentTab)
			btn->render(m_window);

	m_window->display();
}

////////////////////////////////////////////////////////////

void MainMenu::initOptions(sf::Font& t_font, sf::Vector2f t_windowSize)
{
	sf::Texture tex;
	float totalHeight = t_windowSize.y - m_offset * 2; // total size of the background 
	float step = totalHeight / 2 - 75; // how far down each button moves (half the background - button height)
	if (!tex.create(t_windowSize.x * m_screenToButtonWidth, 150)) // create the texture
		std::cout << "Failed to create Tex";

	sf::Vector2f buttonPos{ m_offset, m_offset }; // first button position 
	m_options[0] = createButton(t_font,"AI", &MainMenu::showAITab, buttonPos, tex);
	buttonPos.y += step;
	m_options[1] = createButton(t_font,"Local", &MainMenu::showLocalTab, buttonPos, tex);
	buttonPos.y += step;
	m_options[2] = createButton(t_font,"Network", &MainMenu::showNetworkTab, buttonPos, tex);

}

////////////////////////////////////////////////////////////

void MainMenu::initTabs(sf::Font& t_font, sf::Vector2f t_windowSize)
{
	sf::Texture tex; // texture to hold the button
	tex.create(t_windowSize.x * m_screenToButtonWidth, 100); // create the texture
	float tabHeight = t_windowSize.y - m_offset * 2; // total size of the background
	float centerOfBackground = t_windowSize.x / 4.0f * 3.0f; 
	float xMiddle = centerOfBackground - tex.getSize().x / 2; // offset from the background so the button is centered

	float yMiddle = tabHeight / 2 - 50; // button center on the Y point
	float yStep = tabHeight / 3 - 50;
	// create the buttons 
	m_AI.push_back(createButton(t_font, "Easy", GameType::EASY, {xMiddle,yMiddle - yStep}, tex));
	m_AI.push_back(createButton(t_font, "Medium", GameType::MEDIUM, {xMiddle,yMiddle}, tex));
	m_AI.push_back(createButton(t_font, "Hard", GameType::HARD, {xMiddle,yMiddle + yStep}, tex));

	m_local.push_back(createButton(t_font, "Play", GameType::LOCAL, { xMiddle,yMiddle }, tex));

	m_network.push_back(createButton(t_font, "Host", GameType::HOST, { xMiddle, yMiddle - 100 }, tex));
	m_network.push_back(createButton(t_font, "Join", GameType::CLIENT, { xMiddle, yMiddle + 100 }, tex));
	
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

Button* MainMenu::createButton(sf::Font& t_font,std::string t_name,  GameType t_type, sf::Vector2f t_pos, sf::Texture& t_tex)
{
	Button* btn = new Button(t_font, t_name);
	btn->addFunction<Game, GameType>(m_gameCaller, m_launchGame, t_type);
	btn->setTexture(t_tex);
	btn->setPosition(t_pos);
	return btn;
}

Button* MainMenu::createButton(sf::Font& t_font, std::string t_name, std::function<void(MainMenu*)>t_func, sf::Vector2f t_pos, sf::Texture& t_tex)
{
	Button* btn = new Button(t_font, t_name);
	btn->addFunction<MainMenu>(this, t_func);
	btn->setTexture(t_tex);
	btn->setPosition(t_pos);
	return btn;
}
