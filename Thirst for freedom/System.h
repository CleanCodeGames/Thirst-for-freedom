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

	static sf::RenderWindow* window;									// ���� �� ��� ������
	static sf::Clock clock;												// ����
	static sf::Event event;												// �������
	static sf::View camera;												// ������
	static sf::Font font;												// �����

	static Texture* texture;											// ��� ��������

	static float time;													// ����� ���������
	static int screen_X;												// ���������� ������ �� X
	static int screen_Y;												// ���������� ������ �� Y
	static float screen_Main;											// ���������� ������ ������
	static float screen_1;												// ���������� ������ 1% �� ������
	static bool screen_Is_Wide;											// ������� �����
	static vec2f mouse_Position;										// ������� ������� � ������� ����

	static float RandMinMaxf(float min, float max);						// ��������� ������������� �����
	static int RandMinMaxi(int min, int max);							// ��������� �������������� �����
	static bool RandBool();												// ��������� ����������� ��������
	
	static void Initialize();											// ������������� ���� ����������� ����� (������������ 1 ��� � ������� �����)
	static void GetTimeAndMousePositionion();							// ��������� ����� � ������� ������� (������������ 1 ��� � ������� �����)
	static sf::FloatRect GetVisibleCam();								// ������� ��������� ������
	static enum GAME_STATE { PRELOAD, MAIN_MENU, GAME } game_State;		// ������� ��������� ����
};

