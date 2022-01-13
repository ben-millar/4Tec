#include <Button.h>

Button::Button(sf::Font& t_font, std::string t_buttonText) :
	m_text(t_buttonText, t_font, 50U), m_autoSelect(false)
{
	m_texture.loadFromFile("assets/images/Button.png");
	setTexture(m_texture);
}

////////////////////////////////////////////////////////////

Button::~Button() {}

////////////////////////////////////////////////////////////

void Button::addFunction(Game* t_caller, std::function<void(Game*, GameType, NetworkType, AIDifficulty)> t_func, GameType t_gt, NetworkType t_nt, AIDifficulty t_ai)
{
	m_func = t_func;
	m_gameType = t_gt;
	m_networkType = t_nt;
	m_aiDifficulty = t_ai;
	m_caller = t_caller;
}

////////////////////////////////////////////////////////////

void Button::gainFocus()
{
	m_sprite.setColor(sf::Color(150U, 150U, 150U, 255U));
}

////////////////////////////////////////////////////////////

void Button::loseFocus()
{
	m_sprite.setColor(sf::Color(125U, 125U, 125U, 255U));
}

////////////////////////////////////////////////////////////

void Button::setTexture(sf::Texture& t_texture)
{
	m_sprite.setTexture(t_texture);
	loseFocus();
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
	if (m_func && m_caller)
		m_func(m_caller, m_gameType, m_networkType, m_aiDifficulty);
}

////////////////////////////////////////////////////////////

void Button::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_sprite);
	t_window->draw(m_text);
}

////////////////////////////////////////////////////////////

void Button::setScale(sf::Vector2f t_scale)
{
	m_sprite.setScale(t_scale);
	if (t_scale.x >= 0.75)
		m_text.setCharacterSize(45U);
	else
		m_text.setCharacterSize(32U);
}

////////////////////////////////////////////////////////////

void Button::centerText(sf::Vector2f t_pos)
{
	sf::Vector2f boxSize = { m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height };
	sf::FloatRect textSize = m_text.getGlobalBounds();
	float centerX = t_pos.x + (boxSize.x / 2) - (textSize.width / 2);
	float centerY = t_pos.y + (boxSize.y / 2) - (textSize.height / 2);
	m_text.setPosition(centerX, centerY);
}
