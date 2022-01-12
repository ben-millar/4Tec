#ifndef MAIN_MENU_INCLUDE
#define MAIN_MENU_INCLUDE

#include <Button.h>
#include <iostream>
#include <array>
#include <Globals.h>
#include <vector>
#include <GameData.h>

using Tab = std::vector<Button*>;

class MainMenu
{
public:
	/// <summary>
	/// Constructor for the screen
	/// </summary>
	/// <param name="t_game"> Game class to call function</param>
	/// <param name="t_func"> Function to change screen </param>
	MainMenu(Game* t_game, std::function<void(Game*, GameType, NetworkType, AIDifficulty)> t_func, sf::Font& t_font);

	~MainMenu();

	/// <summary>
	/// Function that will be called to process any events
	/// that occur while the screen is open.
	/// Will be used to handle all player inputs
	/// </summary>
	/// <param name="t_event"> current event </param>
	void processEvents(sf::Event& t_event, sf::RenderWindow* t_window);

	/// <summary>
	/// Render the current screen 
	/// </summary>
	/// <param name="t_window"> window to render it too. </param>
	void render(sf::RenderWindow* t_window);

private:
	void initOptions(sf::Font&, sf::Vector2f);

	/// <summary>
	/// Shows the user the difficulties and allows them to start the game 
	/// </summary>
	void showAITab();

	/// <summary>
	/// Shows the user that starting the game will run a local game 
	/// </summary>
	void showLocalTab();

	/// <summary>
	/// Allows the user to pick host or client
	/// </summary>
	void showNetworkTab();

	Button* createButton(std::string, GameType, NetworkType, AIDifficulty, sf::Vector2f);

	sf::VertexArray m_background;
	std::array<Button*, 3> m_options;
	Tab* m_currentTab;
	Tab m_AI;
	Tab m_local;
	Tab m_network;
	Button* m_currentButton;
	Button* m_tabButton;
	sf::Font m_gameFont;

	Game* m_gameCaller;
	std::function<void(Game*, GameType, NetworkType, AIDifficulty)> m_launchGame;

	float m_screenToButtonWidth{ 4.0f / 9.0f };
	float m_offset{ 10.0f };
};

#endif