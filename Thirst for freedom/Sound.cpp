#include "Sound.h"
// " " + std::to_string(i+1) + " "
Sound::Sound()
{

}

inline void Sound::LoadSound(sf::String file, sf::Sound& s, sf::SoundBuffer& b, float vol)
{
	b.loadFromFile(file);
	s.setBuffer(b);
	s.setVolume(vol);
}

inline void Sound::LoadMusic(sf::String file, sf::Music& m, float vol)
{
	m.openFromFile(file);
	m.setVolume(vol);
}
