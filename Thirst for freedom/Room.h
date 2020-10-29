#pragma once
#include "Terrain.h"
#include "Arnold.h"
class Room :
	public System
{
private:

	Terrain* terrain;
	Wall* wall;
	Unit* unit;
	Arnold* m_Arnold;

	// SpwanBox* spawnBox;

	void LayerTerrain();
	void LayerGrass();
	void LayerDoodas();
	void LayerCollision();
	void LayerSwapnBox();

public:

	static enum DirectionExit { left, top, right, down } m_Dir_Exit;
	static vec2f m_Position;
	static uint m_Size_W, m_Size_H;
	static sf::String* m_Room;

	Room(sf::String type_ID, Arnold* arnold);
};

