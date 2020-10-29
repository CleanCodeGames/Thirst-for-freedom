#pragma once
#include "Arnold.h"
#include "Sun.h"
#include "Room.h"

class Game : 
	public System
{
private:

	Room* room;
	Arnold* arnold;
	Unit* unit;
	void Thread();

public: 

	sf::Thread* thread;
	Game(void);
};