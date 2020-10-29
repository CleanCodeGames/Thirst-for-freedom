#pragma once
#include "sprite.h"
class Button :
	public Sprite
{
protected:

	bool m_isInsideMouse;
	bool m_isClickFixed;
	bool m_isReadyFixed;

public:

	Button(vec2f pos, vec2f size, sf::Texture& texture);
	Button(void);

	virtual void Inside();
	virtual void Fixed();

	virtual void SetClickFixed(bool b);
	virtual void SetReadyFixed(bool b);

	virtual bool GetInsideMouse() const;
	virtual bool GetClickFixed() const;
	virtual bool GetReadyFixed() const;

	virtual void ClearReadyFixed();
};