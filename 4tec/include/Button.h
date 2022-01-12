#ifndef BUTTON_INCLUDE
#define BUTTON_INCLUDE

#include <SFML/Graphics.hpp>

#include <FunctionPointer.h>

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

	/// <summary>
	/// Adds a function to the button where there are no arguments taken
	/// This function can come from any class
	/// </summary>
	/// <typeparam name="T">Class the function comes from</typeparam>
	/// <param name="t_caller">The object calling the function</param>
	/// <param name="t_func">The Function</param>
	template<typename T>
	void addFunction(T* t_caller, std::function<void(T*)> t_func);

	/// <summary>
	/// Overloaded function that allows the button to call a function that accepts one arugment
	/// </summary>
	/// <typeparam name="T">Class Type</typeparam>
	/// <typeparam name="U">Argument Type</typeparam>
	/// <param name="t_caller">Object calling the function</param>
	/// <param name="t_func">The function</param>
	/// <param name="t_arg">The arugment for the function</param>
	template<typename T, typename U>
	void addFunction(T* t_caller, std::function<void(T*,U)> t_func, U t_arg);

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

	FunctionPointer* m_func{nullptr};
	sf::Sprite m_sprite;
	sf::Text m_text;
	bool m_autoSelect;
};

#endif

template<typename T>
inline void Button::addFunction(T* t_caller, std::function<void(T*)> t_func)
{
	m_func = new Function<T>(t_caller, t_func);
	m_autoSelect = true;
}

template<typename T, typename U>
inline void Button::addFunction(T* t_caller, std::function<void(T*, U)> t_func, U t_arg)
{
	m_func = new FunctionArg<T,U>(t_caller, t_func, t_arg);
}
