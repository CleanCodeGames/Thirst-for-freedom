#pragma once
#include<SFML/Audio.hpp>
class Sound
{
private:

	inline void LoadSound(sf::String file, sf::Sound& sound, sf::SoundBuffer& buffer, float volume);
	inline void LoadMusic(sf::String file, sf::Music& music, float volume);

public: Sound();
};

