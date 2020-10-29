#pragma once
#include<SFML\Graphics.hpp>
#include<sstream>
typedef sf::Texture JPG, PNG;
class Texture
{
public:
	
	// Environment
	PNG sun[2];

	// Unit
	PNG arnold;
	PNG moomie;
	PNG soul_Collector;
	PNG crussader;
	PNG tower;

	// Objects
	PNG box;
	PNG skull_Post;

	// Terrain
	PNG tile01;
	PNG tile02;
	PNG tile03;
	PNG tile04;

	// UI
	PNG hp_bar;
	PNG energy_bar;
	PNG ico_Arnold;
	PNG ico_Crussader;
	PNG ico_Moomie;
	PNG ico_Soul_Collector;
	PNG ico_Tower;

	// Missle
	PNG missle_Tower;
	PNG missle_Moomie;


private:

	inline void Load(PNG& t, sf::String file);
	inline void LoadSmoth(PNG& t, sf::String file);

public: Texture(void);
};