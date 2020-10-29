#pragma once
#include "Texture.h"
#include "Sound.h"
#include <Windows.h>
#include <delayimp.h>
#include <dos.h>
#include <iostream>
#include <list>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>

#define virline virtual inline
#define virt virtual
#define inl inline
#define PI 3.14159265f
#define DEG 57.2957795f
#define s_float static_cast<float>
#define s_int static_cast<int>
#define s_bool static_cast<bool>
#define uint unsigned int
typedef sf::Vector2f vec2f;
typedef sf::Keyboard Key;

class System
{
public:

	static sf::RenderWindow* window;									// Окно на все случаи
	static sf::Clock clock;												// Часы
	static sf::Event event;												// Событие
	static sf::View camera;												// Камера
	static sf::Font font;												// Шрифт

	static Texture* texture;											// Все текстуры

	static float time;													// Время прошедшее
	static int screen_X;												// Разрешение экрана по X
	static int screen_Y;												// Разрешение экрана по Y
	static float screen_Main;											// Разрешение экрана основа
	static float screen_1;												// Разрешение экрана 1% от основы
	static bool screen_Is_Wide;											// Широкий экран
	static vec2f mouse_Position;										// Позиция курсора в игровом мире

	static float RandMinMaxf(float min, float max);						// Генерация вещественного числа
	static int RandMinMaxi(int min, int max);							// Генерация целочисленного числа
	static bool RandBool();												// Генерация логического значения
	
	static void Initialize();											// Инициализация всех статических полей (Используется 1 раз в главном цикле)
	static void GetTimeAndMousePositionion();							// Обновляем время и позицию курсора (Используется 1 раз в главном цикле)
	static sf::FloatRect GetVisibleCam();								// Область видимости камеры
	static enum GAME_STATE { PRELOAD, MAIN_MENU, GAME } game_State;		// Текущее состояние игры
};

