#ifndef GAMEPLAY_INCLUDE
#define GAMEPLAY_INCLUDE

#include <BaseScreen.h>
#include <GameManager.h>
#include <TokenManager.h>
#include <TextureManager.h>
#include <Network.h>
#include <AI.h>
#include <PlayerInput.h>

class Gameplay : public BaseScreen
{
public:
	Gameplay();

	/// <summary>
	/// Loads the different game types so it handles 
	/// PVE (Varying difficulties)
	/// PVP (Local) 
	/// PVP (Local-Network)
	/// </summary>
	/// <param name="">What way to run the game</param>
	void loadGame(GameType);

	/// <summary>
	/// Process the events inside the game
	/// </summary>
	/// <param name="t_event">CurrentEvent</param>
	void processEvents(sf::Event& t_event)override;

	/// <summary>
	/// Draw the current Game
	/// </summary>
	void render()override;
private:
	/// <summary>
	/// Load the textures for the game
	/// </summary>
	void loadTextures();

	/// <summary>
	/// Load the shaders for the game
	/// </summary>
	void loadShader();

	sf::Sprite m_boardSprite;
	sf::Sprite m_shadowSprite;

	sf::Shader m_shader;

	GameManager* _gm;
	TokenManager* _tm;

	Network* m_network;
	PlayerInput m_player;
	AI* m_ai;
};


#endif