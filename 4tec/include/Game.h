#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include <GameManager.h>
#include <Globals.h>
#include <Input.h>
#include <Minimax.h>
#include <TextureManager.h>
#include <TokenManager.h>

#include <Network.h>
#include <PlayerInput.h>
#include <InputManager.h>
#include <AI.h>

using namespace std;

enum class GameType
{
	PVE,
	AIvsAI,
	PVP,
	LAN
};

class Game
{
public:
	Game() = default;
	//Game(char choice)
	//{
	//	const char* ip = "192.168.8.148";
	//	const int port = 420;
	//	if (choice == '1')
	//	{
	//		m_network.host(ip,port);
	//	}
	//	else
	//	{
	//		m_network.client(ip,port);
	//	}
	//}
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


	/// <summary>
	/// Function that changes the input types.
	/// Allows the game to run:
	/// Player Vs AI
	/// AI Vs AI
	/// Player Vs Local Player (Same computer)
	/// Player Vs Local Network Player (Same Network)
	/// </summary>
	void setupGame(GameType t_type);

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

	Network m_network;

	sf::Shader m_shader;

	GameManager* _gm;
	TokenManager* m_tokens;
	InputManager* m_inputs;

	PlayerInput* m_player;
	AI* m_ai;
};

#endif