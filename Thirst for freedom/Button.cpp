#include "Button.h"

Button::Button(vec2f pos, vec2f size, sf::Texture& texture)
{
	m_isInsideMouse = m_isClickFixed = m_isReadyFixed = false;
	SetParam(pos, size, true);
}

Button::Button(void)
{
	m_isInsideMouse = m_isClickFixed = m_isReadyFixed = false;
}

void Button::Inside()
{
	if(Contains(mouse_Position))
		if(!m_isInsideMouse) 
			m_isInsideMouse = true;
	else 
		if(m_isInsideMouse) 
			m_isInsideMouse = false;
}

void Button::Fixed()
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:

			if(event.key.code == sf::Mouse::Left)
				if(m_isInsideMouse) 
					if(!m_isClickFixed) {
						m_isClickFixed = true;
						m_Sprite.setScale(0.95f, 0.95f);
					}

			if(event.key.code == sf::Mouse::Right)
				if(m_isReadyFixed) 
					m_isReadyFixed = false;

		break;

		case sf::Event::MouseButtonReleased:

			if(event.key.code == sf::Mouse::Left) {
				if(m_isClickFixed && m_isInsideMouse) 
					if(!m_isReadyFixed) 
						m_isReadyFixed = true;

				if(m_isClickFixed) 
					m_isClickFixed = false;

				m_Sprite.setScale(1.0f, 1.0f);
			}

		break;
	}
}

void Button::SetClickFixed(bool b)
{
	m_isClickFixed = b;
}

void Button::SetReadyFixed(bool b)
{
	m_isReadyFixed = b;
}

bool Button::GetInsideMouse() const
{
	return m_isInsideMouse;
}

bool Button::GetClickFixed() const
{
	return m_isClickFixed;
}

bool Button::GetReadyFixed() const
{
	return m_isReadyFixed;
}

void Button::ClearReadyFixed()
{
	m_isReadyFixed = false;
}
