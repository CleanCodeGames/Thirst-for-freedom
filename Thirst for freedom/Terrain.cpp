#include "Terrain.h"
std::list<Sprite*> Terrain :: terrain_List;

Terrain::Terrain(vec2f position, vec2f size, PNG& texture, bool isOrigin)
	: Sprite(position, size, isOrigin)
{
	SetTexture(texture);
	terrain_List.push_back(this);
}


Terrain::~Terrain(void)
{
}
