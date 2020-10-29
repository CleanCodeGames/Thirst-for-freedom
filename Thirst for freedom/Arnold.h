#pragma once
#include "Unit.h"
#include "Button.h"

class Arnold :
	public Unit
{
private:
	
	bool m_Is_Move_Left;		// Направление движения влево
	bool m_Is_Move_Right;		// Направление движения вправо
	bool m_Is_Move_Down;		// Направление движения вниз
	bool m_Is_Move_Up;			// Направление движения вверх

	bool m_Is_Attack_Can;		// Можно бить

	float m_Energy_Point;			// Энергия для нанесения атак
	int m_Energy_Point_Max;		// Энергии максимальный запас
	int m_Energy_Cost;			// Стоимость атаки
	float m_Energy_Regeneration;// Скорость регенерации энергии

	float m_Factor_Assitude;	// Фактор усталости 0.0 - 1.0

	inl float GetMoveDirection();
	inl void UpdateCamera();
	inl void UpdateBar();
	inl void MobAgro();
	inl void HideNeutralBar(bool hide);
	inl void PickTargetUnit();
	inl void EnergyRegeneration();

	Sprite m_Bar_HP_Arnold;				// Бар здоровья
	Sprite m_Bar_Energy_Arnold;			// Бар енергии
	Sprite m_Ico_Arnold;				// Иконка арнольда
	Sprite m_Indicator_HP_Arnold;		// Индикатор здоровья
	Sprite m_Indicator_MP_Arnold;		// Индикатор маны
	Sprite m_Indicator_Energy_Arnold;	// Индикатор енергии
	Sprite m_Indicator_Coldown_Arnold;	// Индикатор перезарядки атаки

	Sprite m_Bar_HP_Neutral;			// Бар здоровья врага
	Sprite m_Ico_Neutral;				// Иконка врага
	Sprite m_Indicator_HP_Neutral;		// Индикатор здоровья Врага
	Sprite m_Indicator_MP_Neutral;		// Индикатор маны Врага

	Unit* m_Picked_Unit;				// Выбранная цель
	Unit* m_Target_Unit;				// Выбранная цель

	Button* m_Button_Ability;

public:

	void Update();
	void Control();
	
	
	Arnold(vec2f position, vec2f size, void* name_ID);
};

