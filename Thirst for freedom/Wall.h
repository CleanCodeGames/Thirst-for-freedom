#pragma once
#include "Sprite.h"
class Wall :
	public Sprite
{
private:

	bool m_Is_Quad;

public:

	static std::list<Wall*> wall_List;

	virt bool GetIsQuad() const;

	Wall(vec2f position, vec2f size, PNG& texture, bool isQuad);
	~Wall(void);
};

