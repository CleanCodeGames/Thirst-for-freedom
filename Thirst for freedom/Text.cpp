#include "Text.h"

Text::Text(int charSize, bool is_origin, vec2f position, sf::Font& font, sf::String string)
{
	text.setFont(font);
	text.setCharacterSize(static_cast<int>(charSize*screen_1));
	text.setColor(sf::Color(255,255,255,255));
	text.setString(string);
	if(is_origin) text.setOrigin(GetCenter());
	text.setPosition(position*screen_1);
}

Text::Text(int charSize, bool is_origin, vec2f position, sf::Font& font, sf::Color color, sf::String string)
{
	text.setFont(font);
	text.setCharacterSize(charSize*(int)screen_1);
	text.setColor(color);
	text.setString(string);
	if(is_origin) text.setOrigin(GetCenter());
	text.setPosition(position*screen_1);
}

void Text::SetTextString(sf::String string)
{
	text.setString(string);
}

void Text::SetTextStringScore(sf::String string, int score)
{
	text.setString(string+std::to_string(score));
}

void Text::SetColor(sf::Color color)
{
	text.setColor(color);
}

vec2f Text::GetCenter() const
{
	return vec2f(
		text.getGlobalBounds().left + text.getGlobalBounds().width/2.f, 
		text.getGlobalBounds().top + text.getGlobalBounds().height/2.f
		);
}

sf::Text& Text::GetText()
{
	return text;
}