#pragma once
#include "Unit.h"
#include "Button.h"

class Arnold :
	public Unit
{
private:
	
	bool m_Is_Move_Left;		// ����������� �������� �����
	bool m_Is_Move_Right;		// ����������� �������� ������
	bool m_Is_Move_Down;		// ����������� �������� ����
	bool m_Is_Move_Up;			// ����������� �������� �����

	bool m_Is_Attack_Can;		// ����� ����

	float m_Energy_Point;			// ������� ��� ��������� ����
	int m_Energy_Point_Max;		// ������� ������������ �����
	int m_Energy_Cost;			// ��������� �����
	float m_Energy_Regeneration;// �������� ����������� �������

	float m_Factor_Assitude;	// ������ ��������� 0.0 - 1.0

	inl float GetMoveDirection();
	inl void UpdateCamera();
	inl void UpdateBar();
	inl void MobAgro();
	inl void HideNeutralBar(bool hide);
	inl void PickTargetUnit();
	inl void EnergyRegeneration();

	Sprite m_Bar_HP_Arnold;				// ��� ��������
	Sprite m_Bar_Energy_Arnold;			// ��� �������
	Sprite m_Ico_Arnold;				// ������ ��������
	Sprite m_Indicator_HP_Arnold;		// ��������� ��������
	Sprite m_Indicator_MP_Arnold;		// ��������� ����
	Sprite m_Indicator_Energy_Arnold;	// ��������� �������
	Sprite m_Indicator_Coldown_Arnold;	// ��������� ����������� �����

	Sprite m_Bar_HP_Neutral;			// ��� �������� �����
	Sprite m_Ico_Neutral;				// ������ �����
	Sprite m_Indicator_HP_Neutral;		// ��������� �������� �����
	Sprite m_Indicator_MP_Neutral;		// ��������� ���� �����

	Unit* m_Picked_Unit;				// ��������� ����
	Unit* m_Target_Unit;				// ��������� ����

	Button* m_Button_Ability;

public:

	void Update();
	void Control();
	
	
	Arnold(vec2f position, vec2f size, void* name_ID);
};

