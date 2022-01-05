#ifndef BASE_SCREEN_INCLUDE
#define BASE_SCREEN_INCLUDE

enum class Screens {
	MainMenu,
	Gameplay,
	DifficultySelect
};

#include <functional>
#include <SFML/Graphics.hpp>

class Game;

class BaseScreen
{
public:
	BaseScreen(Game* t_caller, std::function<void(Game*, Screens)> t_func) : m_caller(t_caller), m_func(t_func) {};

	virtual void onEnter() = 0;
	virtual void update(sf::Time t_dt) = 0;
	virtual void processEvents(sf::Event& t_event) = 0;
	virtual void render(sf::RenderWindow* t_window) = 0;
	virtual void onExit() = 0;

protected:
	Game* m_caller;
	std::function<void(Game*, Screens)> m_func;
};

#endif