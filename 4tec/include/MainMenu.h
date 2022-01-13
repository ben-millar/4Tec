#ifndef MAIN_MENU_INCLUDE
#define MAIN_MENU_INCLUDE

#include <Button.h>
#include <iostream>
#include <array>
#include <Globals.h>
#include <vector>
#include <GameData.h>

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
	/// <summary>
	/// Setup all the options on the menu
	/// </summary>
	void initOptions();

	/// <summary>
	/// Function to simplify the creation + setup of a button
	/// </summary>
	/// <param name="name"> Name the button displays</param>
	/// <param name="gameType">Parameter to pass to the function</param>
	/// <param name="NetworkType">Parameter to pass to the function</param>
	/// <param name="AIDifficulty">Parameter to pass to the function</param>
	/// <param name="Pos"> where to place the button</param>
	/// <returns></returns>
	Button* createButton(std::string, GameType, NetworkType, AIDifficulty, sf::Vector2f&);

	/// <summary>
	/// Function to simplify the placing of a text object
	/// </summary>
	/// <param name="Text">Object to be placed</param>
	/// <param name="name">What the text shows</param>
	/// <param name="pos">Where the text is placed</param>
	void placeText(sf::Text&,std::string, sf::Vector2f);

	sf::VertexArray m_background;
	
	Button* m_currentButton;
	std::vector<Button*> m_options;
	sf::Font m_gameFont;
	sf::Text m_aiText;
	sf::Text m_localText;

	Game* m_gameCaller;
	std::function<void(Game*, GameType, NetworkType, AIDifficulty)> m_launchGame;
};

#endif