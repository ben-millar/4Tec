#include <Button.h>

Button::~Button()
{
	delete m_func;
}

////////////////////////////////////////////////////////////

void Button::gainFocus()
{
	sf::Color color = (m_autoSelect) ?
		sf::Color(150U, 150U, 150U, 255U) :
		sf::Color(200U, 200U, 200U, 255U);
	m_sprite.setColor(color);
	if (m_autoSelect)
		m_sprite.setScale({ 1.5f,1.0f });
}

////////////////////////////////////////////////////////////

void Button::loseFocus()
{
	m_sprite.setColor(sf::Color(100U, 100U, 100U, 255U));
	if (m_autoSelect)
		m_sprite.setScale({ 1.0f,1.0f });
}

////////////////////////////////////////////////////////////

void Button::setTexture(sf::Texture& t_texture)
{
	m_sprite.setTexture(t_texture);
	m_sprite.setColor(sf::Color(100U, 100U, 100U, 255U));
}

////////////////////////////////////////////////////////////

void Button::setPosition(sf::Vector2f t_pos)
{
	m_sprite.setPosition(t_pos);
	centerText(t_pos);
}

////////////////////////////////////////////////////////////

void Button::activate()
{
	gainFocus();
	if (m_func)
		m_func->call();
}

////////////////////////////////////////////////////////////

void Button::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_sprite);
	t_window->draw(m_text);
}

////////////////////////////////////////////////////////////

void Button::centerText(sf::Vector2f t_pos)
{
	sf::FloatRect boxSize = m_sprite.getGlobalBounds();
	sf::FloatRect textSize = m_text.getGlobalBounds();
	float centerX = t_pos.x + (boxSize.width / 2) - (textSize.width / 2);
	float centerY = t_pos.y + (boxSize.height / 2) - (textSize.height / 2);
	m_text.setPosition(centerX, centerY);
}

