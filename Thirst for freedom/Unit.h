#pragma once
#include "Wall.h"

class Unit :
	public Sprite
{
protected:

	float m_Speed_Movement;				// �������� �����������
	float m_Speed_Movement_Default;		// �������� ����������� �����������
	float m_Frame_Timer;				// �������� ��������
	int m_Frame;						// ������� ����


	int m_Attack_Damage;				// ��������� ���� � ����
	float m_Attack_Dist;				// ��������� �����
	float m_Attack_Coldown;				// ���������� ����� �������
	float m_Attack_Coldown_CONST;		// ���������� ����� ������� ���������
	float m_Attack_Delay_Time;			// ����� �������� �������� �����
	float m_Attack_Delay_Time_CONST;	// ����� �������� �������� ����� ���������

	int m_Hit_Point;					// ��������
	int m_Hit_Point_Max;				// ������������ ����� ��������
	int m_Mana_Point;					// ����
	int m_Mana_Point_Max;				// ������������ ����� ����

	bool m_Is_Life;						// ���
	bool m_Is_Attack_Damage_Deal;		// ���� �� �������� ����
	bool m_Is_Attack_Delay;				// ���� ��� ����������� �� �������� ����� �� �����
	bool m_Is_Melee;					// ������� ���

	float m_Corpse_Timer;				// ����� ���������� �����

	vec2f m_Spawn_Point;				// ����� ������
	bool m_Is_Agro;						// ��������� � ����� �� �����
	bool m_Is_Agressive;				// ��������� �� ������� ������
	bool m_Is_Escape;					// ������������ �� �� ����� ������

	enum STATE { ATTACK_DEAL, CAST_ABILITY_TARGET, CAST_ABILITY_CHANNEL, FOLLOW_TO_TARGET, STAND, DIES, RETURN_TO_SPAWN } m_State; // ���������

	void* m_ID_name;					// ������������� ����

	static float DIST_AGRESSIVE_ON;		// ��������� ��������� ������� ��������
	static float DIST_AGRESSIVE_OFF;	// ��������� �������� ������� � ������
	static float DIST_LOST_TARGET;		// ��������� ������ �������� � ����

public:

	static std::list<Unit*> unit_List;

	virt void EscapeToSpawn();									// ������������ �� �����
	virt void SetAgro(bool agro);								// ��������
	virt bool GetAgressive() const;								// �����������
	virt bool GetAgro() const;									// ��������� � ����� �� �����
	virt bool GetIsEscape() const;								// ������������ �� �� ����� ������
	virt vec2f GetSpawnPoint() const;							// ����� ������
	
	virt void Attack(Unit* attacked);							// �������� �������� �����
	virt void AttackColdowner();								// ������������ �����
	virt void AttackDealDamage(Unit* damaged);					// ������� ����
	virt float GetAttackColdown() const;						// ����� �������� ����� �������
	virt int GetAttackDamage() const;							// ���������� ����� ���������� ����������
	virt float GetAttackDist() const;							// ��������� �����
	virt bool GetIsAttackDelay() const;							// ���� ��� ����������� �� �������� ����� �� �����
	virt void AttackDelay();									// ���������� �����

	virt void RestoreHp(int restore);							// ������������ �������� �� restore ��.
	virt void RestoreMP(int restore);							// ������������ ���� �� restore ��.
	virt void Revive(vec2f position, uint HP, uint MP);			// ���������� � ��������� �������� � ���� � ��������� �����
	virt void Revive(vec2f position);							// ���������� � ������ ��������� � �����

	virt void SetHpMax(uint hp);								// �������� ������������ �������� ��������
	virt void SetMpMax(uint mp);								// �������� ������������ �������� ����
	virt void SetHp(uint hp);									// �������� ������� �������� ��������
	virt void SetMp(uint mp);									// �������� ������� �������� ��������
	virt void SetSpeed(float speed);							// �������� �������� �����������
	virt void SetState(const uint state);						// �������� ���������
	virt void Corpse();											// ��������� ����

	virt int GetHpMax() const;									// ������������ ����� ��������
	virt int GetMpMax() const;									// ������������ ����� ����
	virt int GetHp() const;										// �������� �������
	virt int GetMp() const;										// ���� �������
	virt enum STATE GetState() const;							// ��������� ��������
	virt float GetMoveSpeed() const;							// �������� �����������
	virt bool GetIsLife() const;								// �����
	virt float GetCorpseTimer() const;							// ���� �������� �����������
	virt void* GetIdName();										// ������������� ����
	virt void AnimationPlay(void* animID);						// �������������� ��������

	Unit(vec2f position, vec2f size, void* name_ID);
};

class Missle :
	public Sprite
{
private:

	float m_Misle_Speed;
	bool m_Is_Life;
	Unit* m_Unit_Target;
	Unit* m_Unit_Owner;
	Sprite m2;

public:

	static std::list<Missle*> missle_List;
	Sprite GetSpriteM2();
	virt void Update();
	virt void Draw();
	Unit* GetTarget();
	virt bool GetIsLife() const;
	Missle(vec2f size, Unit* owner, Unit* target, float speed, PNG& png);
};
