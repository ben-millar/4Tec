#ifndef BASE_SCREEN_INCLUDE
#define BASE_SCREEN_INCLUDE

#include <functional>
#include <SFML/Graphics.hpp>
#include <GameData.h>

class Game;

/// <summary>
/// Base class that other screens can inherit from 
/// </summary>
class BaseScreen
{
public:
	BaseScreen()=default;

	/// <summary>
	/// Handles events that occur on the screen
	/// </summary>
	/// <param name="t_event">Current Event</param>
	virtual void processEvents(sf::Event& t_event) = 0;

	/// <summary>
	/// Draws the screen
	/// </summary>
	virtual void render() = 0;

	/// <summary>
	/// Adds a window to draw the screen on
	/// </summary>
	/// <param name="t_window"></param>
	virtual void addWindow(sf::RenderWindow* t_window) { m_window = t_window; }

protected:
	sf::RenderWindow* m_window;
};

#endif