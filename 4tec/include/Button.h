#ifndef BUTTON_INCLUDE
#define BUTTON_INCLUDE

#include <SFML/Graphics.hpp>
#include <GameData.h>
#include <functional>

class Game;

class Button
{
public:
	/// <summary>
	/// Overloaded Constructor that allows you to initialize the font with the button
	/// </summary>
	/// <param name="t_font">Font for the button</param>
	/// <param name="t_buttonText">What the button will show</param>
	Button(sf::Font& t_font, std::string t_buttonText) : m_text(t_buttonText, t_font, 58U), m_autoSelect(false) {};
	~Button();
	void addFunction(Game* t_caller,std::function<void(Game*, GameType, NetworkType, AIDifficulty)> t_func, GameType t_gt, NetworkType t_nt, AIDifficulty t_ai);

	/// <summary>
	/// Gives a visual aid to show the button is highlighted
	/// </summary>
	void gainFocus();

	/// <summary>
	/// Gives a visual aid to show the button is no longer highlighted
	/// </summary>
	void loseFocus();

	/// <summary>
	/// Allows for easy setting of the texture
	/// </summary>
	/// <param name="t_texture"></param>
	void setTexture(sf::Texture& t_texture);

	/// <summary>
	/// Allows the user to position the button
	/// </summary>
	/// <param name="t_pos">Where to place the button</param>
	void setPosition(sf::Vector2f t_pos);

	/// <summary>
	/// Calls the function associated with the button provided it has one
	/// </summary>
	void activate();

	/// <summary>
	/// Draw the button so we can see it 
	/// </summary>
	/// <param name="t_window">Window to draw the button to</param>
	void render(sf::RenderWindow* t_window);

	/// <summary>
	/// Allows the modification of the sprite outside the class
	/// used to check bounds
	/// </summary>
	/// <returns>The sprite for the button</returns>
	sf::Sprite& getSprite() { return m_sprite; }
private:
	/// <summary>
	/// Function to position the text in the center of the button 
	/// </summary>
	/// <param name="t_pos"></param>
	void centerText(sf::Vector2f t_pos);
	std::function<void(Game*, GameType, NetworkType, AIDifficulty)> m_func;
	GameType m_gameType;
	NetworkType m_networkType;
	AIDifficulty m_aiDifficulty;
	Game* m_caller;
	sf::Sprite m_sprite;
	sf::Text m_text;
	bool m_autoSelect;
};
#endif
