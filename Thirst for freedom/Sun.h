#pragma once
#include "Sprite.h"
#include "Texture.h"

class Sun :
	public Sprite
{
private:

	Sprite m_Sun;
	float m_Speed;

public:

	void Update();
	Sun(vec2f position, vec2f size);
	~Sun(void);
};

