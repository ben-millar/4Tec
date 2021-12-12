#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include <GameManager.h>
#include <Globals.h>
#include <Input.h>
#include <TextureManager.h>
#include <TokenManager.h>

using namespace std;

class Game
{
public:
	Game() = default;
	~Game() = default;

	/// <summary>
	/// Initializes and starts the game loop
	/// </summary>
	void run();

	/// <summary>
	/// Loads in fonts from file
	/// </summary>
	void loadFont();

	/// <summary>
	/// Loads in and assigns textures
	/// </summary>
	void loadTextures();

	void loadShader();

	/// <summary>
	/// Handles system events (input, etc.)
	/// </summary>
	void processEvents();

	/// <summary>
	/// Called once every game tick
	/// </summary>
	/// <param name="t_dTime">Time in seconds since the last update</param>
	void update(sf::Time t_dTime);

	/// <summary>
	/// Clears, redraws and displays the framebuffer
	/// </summary>
	void render();

private:
	/// <summary>
	/// Creates an sf::RenderWindow on the stack
	/// </summary>
	/// <param name="t_title">Title for the sf::RenderWindow</param>
	/// <returns>A pointer to a stack-allocated sf::RenderWindow</returns>
	sf::RenderWindow* createWindow(std::string t_title);
	sf::RenderWindow* m_window{ nullptr };

	sf::Font m_robotoTTF;
	sf::Text m_text;

	sf::Sprite m_boardSprite;
	sf::Sprite m_shadowSprite;

	sf::Shader m_shader;

	GameManager* _gm;
	TokenManager m_tokens;
};

#endif