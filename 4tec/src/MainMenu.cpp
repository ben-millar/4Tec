#include <MainMenu.h>

MainMenu::MainMenu(Game* t_game, std::function<void(Game*, GameType, NetworkType, AIDifficulty)> t_func, sf::Font& t_font) :
	m_gameCaller(t_game),
	m_launchGame(t_func),
	m_background(sf::Quads),
	m_gameFont(t_font)
{
	m_buttonTex.loadFromFile("assets/images/Button.png");
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
	float screenToButtonWidth = 4.0f / 9.0f;
	sf::Vector2f windowSize;
	if (SCREEN_HEIGHT < 780u)
	{
		windowSize = { 531.0f, 585.0f };
		m_buttonScale = { 0.5f, 0.5f };
	}
	else if (SCREEN_HEIGHT < 975u)
	{
		windowSize = { 708.0f, 780.0f };
		m_buttonScale = { 0.75f, 0.75f };
	}
	else
	{
		windowSize = { 885.0f, 975.0f };
		m_buttonScale = { 1.0f,1.0f };
	}

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
	placeText(m_localText, "Local", { windowSize.x / 2, windowSize.y /2 + offset });

	//create variables to be used for button placement
	float buttonWidth = m_buttonTex.getSize().x * m_buttonScale.x;
	float buttonHeight = m_buttonTex.getSize().y * m_buttonScale.y;
	sf::Vector2f tabDimensions = { windowSize.x - offset * 2, windowSize.y / 2 - offset * 2 };
	sf::Vector2f startPos{ offset*2, offset*3 + m_aiText.getGlobalBounds().height};
	m_options.push_back(createButton("Easy", GameType::AI, NetworkType::NONE, AIDifficulty::EASY, startPos));

	startPos = { windowSize.x - offset * 2 - buttonWidth,
		startPos.y };
	m_options.push_back(createButton("Medium", GameType::AI, NetworkType::NONE, AIDifficulty::MEDIUM, startPos));

	startPos = { offset * 2, tabDimensions.y - (buttonHeight + offset)};
	m_options.push_back(createButton("Hard", GameType::AI, NetworkType::NONE, AIDifficulty::HARD, startPos));

	startPos = { windowSize.x - offset* 2 - buttonWidth,
		tabDimensions.y - (buttonHeight + offset)};
	m_options.push_back(createButton("AI vs AI", GameType::AIvAI, NetworkType::NONE, AIDifficulty::HARD, startPos));

	startPos = { windowSize.x / 2 - buttonWidth / 2,
		windowSize.y / 2 + offset * 3 + m_localText.getGlobalBounds().height};
	m_options.push_back(createButton("PVP", GameType::LOCAL, NetworkType::NONE, AIDifficulty::NONE, startPos));

	startPos.y = windowSize.y - offset*2 - buttonHeight;
	m_options.push_back(createButton("Join", GameType::ONLINE, NetworkType::CLIENT, AIDifficulty::NONE, startPos));

	startPos.y = windowSize.y / 2 + offset * 2 + tabDimensions.y / 2 - buttonHeight /2;
	m_options.push_back(createButton("Host", GameType::ONLINE, NetworkType::HOST, AIDifficulty::NONE, startPos));
}

////////////////////////////////////////////////////////////

Button* MainMenu::createButton(std::string t_name, GameType t_gt, NetworkType t_nt, AIDifficulty t_ai, sf::Vector2f& t_pos)
{
	sf::Texture tex;
	tex.create(300, 100);
	Button* btn = new Button(m_gameFont, t_name);
	btn->addFunction(m_gameCaller, m_launchGame, t_gt, t_nt, t_ai);

	btn->setScale(m_buttonScale);
	btn->setPosition(t_pos);
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