#include <MainMenu.h>

MainMenu::MainMenu(Game* t_game, std::function<void(Game*, GameType, NetworkType, AIDifficulty)> t_func, sf::Font& t_font) :
	m_gameCaller(t_game),
	m_launchGame(t_func),
	m_background(sf::Quads),
	m_gameFont(t_font)
{
	initOptions();
}

////////////////////////////////////////////////////////////

MainMenu::~MainMenu()
{
	for (auto& btn : m_options)
		delete btn;
}

////////////////////////////////////////////////////////////

void MainMenu::processEvents(sf::Event& t_event, sf::RenderWindow* t_window)
{
	if (t_event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*t_window));

		if (m_currentButton)
			if (!m_currentButton->getSprite().getGlobalBounds().contains(pos))
			{
				m_currentButton->loseFocus();
				m_currentButton = nullptr;
			}
			else
				return;

		for(auto btn : m_options)
			if (btn->getSprite().getGlobalBounds().contains(pos))
			{
				if (btn != m_currentButton)
				{
					if (m_currentButton)
						m_currentButton->loseFocus();
					m_currentButton = btn;
					m_currentButton->gainFocus();
				}
			}
	}
	else if (t_event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*t_window));
		if (m_currentButton)
			if (m_currentButton->getSprite().getGlobalBounds().contains(pos))
				m_currentButton->activate();
	}
}

////////////////////////////////////////////////////////////

void MainMenu::render(sf::RenderWindow* t_window)
{
	t_window->clear(sf::Color(50U, 50U, 50U, 255U));

	t_window->draw(m_background);
	t_window->draw(m_aiText);
	t_window->draw(m_localText);
	for (Button* btn : m_options)
		btn->render(t_window);

	t_window->display();
}

////////////////////////////////////////////////////////////

void MainMenu::initOptions()
{
	sf::Color baseColor{ 100U,100U,100U,255U };
	float offset = 10.0f;
	sf::Vector2f windowSize;
	if (SCREEN_HEIGHT < 780u)
		windowSize = { 531.0f, 585.0f };
	else if (SCREEN_HEIGHT < 975u)
		windowSize = { 708.0f, 780.0f };
	else
		windowSize = { 885.0f, 975.0f };

	m_background.append({ {offset,offset},baseColor });
	m_background.append({ {windowSize.x - offset,offset},baseColor });
	m_background.append({ {windowSize.x - offset,(windowSize.y / 2) - offset},baseColor });
	m_background.append({ {offset,(windowSize.y / 2) - offset},baseColor });

	m_background.append({ {offset,(windowSize.y / 2) + offset},baseColor });
	m_background.append({ {windowSize.x - offset,(windowSize.y / 2) + offset},baseColor });
	m_background.append({ {windowSize.x - offset,windowSize.y - offset},baseColor });
	m_background.append({ {  offset,windowSize.y - offset},baseColor });

	placeText(m_aiText, "AI", { windowSize.x / 2, offset });
	placeText(m_localText, "Local", { windowSize.x / 2, windowSize.y / 2 + offset });

	sf::Vector2f startPos{ windowSize.x / 2 - 150, offset + 40 };

	m_options.push_back(createButton("Easy", GameType::AI, NetworkType::NONE, AIDifficulty::EASY, startPos));
	m_options.push_back(createButton("Medium", GameType::AI, NetworkType::NONE, AIDifficulty::MEDIUM, startPos));
	m_options.push_back(createButton("Hard", GameType::AI, NetworkType::NONE, AIDifficulty::HARD, startPos));

	startPos = { windowSize.x / 2 - 150, windowSize.y / 2 + offset + 40 };
	m_options.push_back(createButton("PVP", GameType::LOCAL, NetworkType::NONE, AIDifficulty::NONE, startPos));
	m_options.push_back(createButton("Host", GameType::ONLINE, NetworkType::HOST, AIDifficulty::NONE, startPos));
	m_options.push_back(createButton("Join", GameType::ONLINE, NetworkType::CLIENT, AIDifficulty::NONE, startPos));
}

////////////////////////////////////////////////////////////

Button* MainMenu::createButton(std::string t_name, GameType t_gt, NetworkType t_nt, AIDifficulty t_ai, sf::Vector2f& t_pos)
{
	sf::Texture tex;
	tex.create(300, 100);
	Button* btn = new Button(m_gameFont, t_name);
	btn->addFunction(m_gameCaller, m_launchGame, t_gt, t_nt, t_ai);
	btn->setTexture(tex);
	btn->setPosition(t_pos);
	t_pos.y += 110;
	return btn;
}

////////////////////////////////////////////////////////////

void MainMenu::placeText(sf::Text& t_text, std::string t_name, sf::Vector2f t_pos)
{
	t_text.setFont(m_gameFont);
	t_text.setString(t_name);
	sf::Vector2f pos = { t_pos.x - t_text.getGlobalBounds().width / 2, t_pos.y };
	t_text.setPosition(pos);
}