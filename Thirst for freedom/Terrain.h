#pragma once
#include"Sprite.h"

class Terrain :
	public Sprite
{
public:
	static std::list<Sprite*> terrain_List;
	Terrain(vec2f position, vec2f size, PNG& texture, bool isOrigin);
	~Terrain(void);
};

