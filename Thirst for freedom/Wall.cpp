#include "Wall.h"

std::list<Wall*> Wall :: wall_List;


Wall :: Wall(vec2f position, vec2f size, PNG& texture, bool isQuad) :
	Sprite(position, size, true)
{
	m_Is_Quad = isQuad;
	SetTexture(texture);
	wall_List.push_back(this);
}

bool Wall :: GetIsQuad() const
{
	return m_Is_Quad;
}

Wall :: ~Wall(void)
{
}
