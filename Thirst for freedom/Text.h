#pragma once
#include "System.h"


typedef sf::Vector2f vec2f;

class Text :
	public System
{
protected: 
	
	sf::Text text;

public:

	Text(int charSize, bool is_orig, vec2f position, sf::Font& font, sf::String string);
	Text(int charSize, bool is_orig, vec2f position, sf::Font& font, sf::Color color, sf::String string);

	sf::Text& GetText();
	vec2f GetCenter() const;
	
	void SetColor(sf::Color color);
	void SetTextString(sf::String string);
	void SetTextStringScore(sf::String string, int score);
};