#include "Room.h"

Room :: DirectionExit Room :: m_Dir_Exit;
vec2f Room :: m_Position;
uint Room :: m_Size_W, Room :: m_Size_H;
sf::String* Room :: m_Room;

Room::Room(sf::String type_ID, Arnold* arnold)
{
	m_Arnold = arnold;

	#pragma region
	if(type_ID == "001")
	{
		m_Size_W = 15;
		m_Size_H = 15;
		m_Room = new sf::String[m_Size_W];

		// Земля
		//=========================
		m_Room[0] = "               ";	// 1 = Чёрная плитка
		m_Room[1] = " 4444444444444 ";	// 2 = Красная плитка
		m_Room[2] = " 4111111111114 ";	// 3 = Зелёная мелкая плитка
		m_Room[3] = " 4122222222214 ";	// 4 = Зелёная трава
		m_Room[4] = " 4122133312214 ";	// 
		m_Room[5] = " 4121111111214 ";	// 
		m_Room[6] = " 4123122213214 ";	// 
		m_Room[7] = " 4123122213214 ";	// 
		m_Room[8] = " 4123122213214 ";	// 
		m_Room[9] = " 4121111111214 ";	// 
		m_Room[10]= " 4122133312214 ";	// 
		m_Room[11]= " 4122222222214 ";	// 
		m_Room[12]= " 4111111111114 ";	// 
		m_Room[13]= " 4444444444444 ";	// 
		m_Room[14]= "               ";	// 
		//=========================
		LayerTerrain();





		// Трава кусты
		//=========================
		m_Room[0] = "               ";	// 
		m_Room[1] = "               ";	// 
		m_Room[2] = "               ";	// 
		m_Room[3] = "               ";	// 
		m_Room[4] = "               ";	// 
		m_Room[5] = "               ";	// 
		m_Room[6] = "               ";	// 
		m_Room[7] = "               ";	// 
		m_Room[8] = "               ";	// 
		m_Room[9] = "               ";	// 
		m_Room[10]= "               ";	// 
		m_Room[11]= "               ";	// 
		m_Room[12]= "               ";	// 
		m_Room[13]= "               ";	// 
		m_Room[14]= "               ";	// 
		//=========================
		LayerGrass();

		// Декорации
		//=========================
		m_Room[0] = "               ";	// 
		m_Room[1] = "               ";	// 
		m_Room[2] = "               ";	// 
		m_Room[3] = "               ";	// 
		m_Room[4] = "               ";	// 
		m_Room[5] = "               ";	// 
		m_Room[6] = "               ";	// 
		m_Room[7] = "               ";	// 
		m_Room[8] = "               ";	// 
		m_Room[9] = "               ";	// 
		m_Room[10]= "               ";	// 
		m_Room[11]= "               ";	// 
		m_Room[12]= "               ";	// 
		m_Room[13]= "               ";	// 
		m_Room[14]= "               ";	// 
		//=========================
		LayerDoodas();

		// Столкновения
		//=========================
		m_Room[0] = "WWWWWWWWWWWWWWW";	// W = Стена
		m_Room[1] = "W             W";	// S = Столб
		m_Room[2] = "W             W";	// 
		m_Room[3] = "W             W";	// 
		m_Room[4] = "W S S S S S S W";	// 
		m_Room[5] = "W             W";	// 
		m_Room[6] = "W             W";	// 
		m_Room[7] = "W             W";	// 
		m_Room[8] = "W             W";	// 
		m_Room[9] = "W             W";	// 
		m_Room[10]= "W S S S S S S W";	// 
		m_Room[11]= "W             W";	// 
		m_Room[12]= "W             W";	// 
		m_Room[13]= "W             W";	// 
		m_Room[14]= "WWWWWWWWWWWWWWW";	// 
		//=========================
		LayerCollision();

		// Спавнеры
		//=========================
		m_Room[0] = "               ";	// A = Арнольд
		m_Room[1] = " E     D     B ";	// B = Мумия
		m_Room[2] = "               ";	// C = Башня
		m_Room[3] = "               ";	// D = Душекрад
		m_Room[4] = "               ";	// E = Рыцарь
		m_Room[5] = "               ";	// 
		m_Room[6] = "               ";	// 
		m_Room[7] = " C     A     C ";	// 
		m_Room[8] = "               ";	// 
		m_Room[9] = "               ";	// 
		m_Room[10]= "               ";	// 
		m_Room[11]= "               ";	// 
		m_Room[12]= "               ";	// 
		m_Room[13]= " B     D     E ";	// 
		m_Room[14]= "               ";	// 
		//=========================
		LayerSwapnBox();
	}

#pragma endregion Type 1
}

void Room :: LayerTerrain()
{
	for(int h = 0; h < m_Size_H; h++)
		for(int w = 0; w < m_Size_W; w++)
		{
			if (m_Room[h][w] == '1') terrain = new Terrain(vec2f(-50 + w * 10, -50 + h * 10), vec2f(10,10), texture->tile01, true);
			if (m_Room[h][w] == '2') terrain = new Terrain(vec2f(-50 + w * 10, -50 + h * 10), vec2f(10,10), texture->tile02, true);
			if (m_Room[h][w] == '3') terrain = new Terrain(vec2f(-50 + w * 10, -50 + h * 10), vec2f(10,10), texture->tile03, true);
			if (m_Room[h][w] == '4') terrain = new Terrain(vec2f(-50 + w * 10, -50 + h * 10), vec2f(10,10), texture->tile04, true);
		}
}

void Room :: LayerGrass()
{
	for(int h = 0; h < m_Size_H; h++)
		for(int w = 0; w < m_Size_W; w++)
		{

		}
}

void Room :: LayerDoodas()
{
	for(int h = 0; h < m_Size_H; h++)
		for(int w = 0; w < m_Size_W; w++)
		{

		}
}

void Room :: LayerCollision()
{
	for(int h = 0; h < m_Size_H; h++)
		for(int w = 0; w < m_Size_W; w++)
		{
			if (m_Room[h][w] == 'W') wall = new Wall(vec2f(-50 + w * 10, -50 + h * 10), vec2f(10,10), texture->box, true);
			if (m_Room[h][w] == 'S') wall = new Wall(vec2f(-50 + w * 10, -50 + h * 10), vec2f(10,10), texture->skull_Post, false);
		}
}

//A = Арнольд
//B = Мумия
//C = Башня
//D = Душекрад
//E = Рыцарь
void Room :: LayerSwapnBox()
{
	for(int h = 0; h < m_Size_H; h++)
		for(int w = 0; w < m_Size_W; w++)
		{
			if(m_Room[h][w] == 'A') 
			{ 
				m_Arnold->SetPos(vec2f(-50 + w * 10, -50 + h * 10)*screen_1);
				camera.setCenter(m_Arnold->GetPos());
			}
			if(m_Room[h][w] == 'B') unit = new Unit(vec2f(-50 + w * 10, -50 + h * 10), vec2f(4,5), "Moomie");
			if(m_Room[h][w] == 'C') unit = new Unit(vec2f(-50 + w * 10, -50 + h * 10), vec2f(4,5), "Tower");
			if(m_Room[h][w] == 'D') unit = new Unit(vec2f(-50 + w * 10, -50 + h * 10), vec2f(4,5), "SoulCollector");
			if(m_Room[h][w] == 'E') unit = new Unit(vec2f(-50 + w * 10, -50 + h * 10), vec2f(4,5), "Crussader");
		}
}
