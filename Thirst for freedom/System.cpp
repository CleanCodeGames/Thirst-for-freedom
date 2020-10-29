#include "System.h"

sf::RenderWindow*	System :: window;
sf::Clock			System :: clock;
Texture*			System :: texture;
sf::Event			System :: event;
sf::View			System :: camera;
sf::Font			System :: font;
float				System :: time;
int					System :: screen_X;
int					System :: screen_Y; 
float				System :: screen_Main; 
float				System :: screen_1;
bool				System :: screen_Is_Wide;
sf::Vector2f		System :: mouse_Position;
System::GAME_STATE	System :: game_State;

sf::FloatRect System :: GetVisibleCam()
{
	return sf::FloatRect(
		s_float(camera.getCenter().x - screen_X/2.f), 
		s_float(camera.getCenter().y - screen_Y/2.f), 
		s_float(screen_X), 
		s_float(screen_Y));
}

float System :: RandMinMaxf(float min, float max)
{
	std::uniform_real_distribution<float> rand(min, max);
	return s_float(rand(std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())));
}

int System :: RandMinMaxi(int min, int max)
{
	std::uniform_int_distribution<int> rand(min, max);
	return s_int(rand(std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())));
}

bool System :: RandBool()
{
	std::uniform_int_distribution<int> rand(0, 1);
	return s_bool(rand(std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())));
}

void System :: GetTimeAndMousePositionion()
{
	time = clock.getElapsedTime().asMicroseconds() / 1000.f, clock.restart(); 
	if(time > 200.f) time = 0.f;
	mouse_Position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void System :: Initialize()
{

	#pragma region

	screen_X = GetSystemMetrics(0);
	screen_Y = GetSystemMetrics(1);

	if(screen_X == 1280 || screen_X == 1360 || screen_X == 1366 || screen_X == 1920)
	{
		if(screen_Y == 720 || screen_Y == 768 || screen_Y == 800 || screen_Y == 1080) 
			screen_Is_Wide = true;
		else 
			screen_Is_Wide = false;
	}

	if(screen_X > screen_Y) screen_Main = screen_Y;
	else screen_Main = screen_X;

	screen_1 = screen_Main / 100.f;

#pragma endregion Проверка разрешения экрана

	game_State = GAME_STATE::GAME;
	texture = new Texture;
	window = new sf::RenderWindow(sf::VideoMode(screen_X,screen_Y), "Arnold", sf::Style::Default, sf::ContextSettings(32, 8, 8, 3, 2));
	camera.reset(sf::FloatRect(0.0f, 0.0f, s_float(screen_X), s_float(screen_Y)));
	camera.setCenter(0,0);
	window->setView(camera);
}