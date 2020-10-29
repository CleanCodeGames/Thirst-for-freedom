#include "Texture.h"
// " " + std::to_string(i+1) + " "
Texture::Texture(void)
{
	// Environment
	LoadSmoth(sun[0], "Environment/Sun1.png");
	LoadSmoth(sun[1], "Environment/Sun2.png");

	// Unit
	LoadSmoth(arnold, "Unit/Arnold.png");
	LoadSmoth(moomie, "Unit/Moomie.png");
	LoadSmoth(tower, "Unit/Tower.png");
	LoadSmoth(crussader, "Unit/Crussader.png");
	LoadSmoth(soul_Collector, "Unit/SoulCollector.png");

	// Terrain
	LoadSmoth(tile01, "Terrain/tile01.png");
	LoadSmoth(tile02, "Terrain/tile02.png");
	LoadSmoth(tile03, "Terrain/tile03.png");
	LoadSmoth(tile04, "Terrain/tile04.png");

	// Objects
	LoadSmoth(box, "Object/Box.png");
	LoadSmoth(skull_Post, "Object/SkullPost.png");
	
	// Missle
	LoadSmoth(missle_Tower, "Missle/Missle_Tower.png");
	LoadSmoth(missle_Moomie, "Missle/missle_Moomie.png");

	// UI
	Load(hp_bar, "UI/Bar/HpBar.png");
	Load(energy_bar, "UI/Bar/EnergyBar.png");

	Load(ico_Arnold, "UI/Avatar/Ico_Arnold.png");
	Load(ico_Crussader, "UI/Avatar/ico_Crussader.png");
	Load(ico_Moomie, "UI/Avatar/ico_Moomie.png");
	Load(ico_Soul_Collector, "UI/Avatar/ico_Soul_Collector.png");
	Load(ico_Tower, "UI/Avatar/ico_Tower.png");

}

inline void Texture::LoadSmoth(PNG& t, sf::String file)
{
	t.loadFromFile("Textures/"+file);
	t.setSmooth(true);
}

inline void Texture::Load(PNG& t, sf::String file)
{
	t.loadFromFile("Textures/"+file);
}