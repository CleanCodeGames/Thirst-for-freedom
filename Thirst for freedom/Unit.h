#pragma once
#include "Wall.h"

class Unit :
	public Sprite
{
protected:

	float m_Speed_Movement;				// Скорость перемещения
	float m_Speed_Movement_Default;		// Скорость перемещения изначальная
	float m_Frame_Timer;				// Скорость анимации
	int m_Frame;						// Текущий кадр


	int m_Attack_Damage;				// Наносимый урон с руки
	float m_Attack_Dist;				// Дальность атаки
	float m_Attack_Coldown;				// Промежуток между атаками
	float m_Attack_Coldown_CONST;		// Промежуток между атаками константа
	float m_Attack_Delay_Time;			// Время задержки анимации атаки
	float m_Attack_Delay_Time_CONST;	// Время задержки анимации атаки константа

	int m_Hit_Point;					// Здоровье
	int m_Hit_Point_Max;				// Максимальный запас здоровья
	int m_Mana_Point;					// Мана
	int m_Mana_Point_Max;				// Максимальный запас маны

	bool m_Is_Life;						// Жив
	bool m_Is_Attack_Damage_Deal;		// Пора ли наносить урон
	bool m_Is_Attack_Delay;				// Если уже замахнулись то проводим атаку до конца
	bool m_Is_Melee;					// Ближний бой

	float m_Corpse_Timer;				// Время разложения трупа

	vec2f m_Spawn_Point;				// Точка спавна
	bool m_Is_Agro;						// Заагрился и бежит за целью
	bool m_Is_Agressive;				// Пассивный не агрится первый
	bool m_Is_Escape;					// Возвращается ли на точку спавна

	enum STATE { ATTACK_DEAL, CAST_ABILITY_TARGET, CAST_ABILITY_CHANNEL, FOLLOW_TO_TARGET, STAND, DIES, RETURN_TO_SPAWN } m_State; // Состояние

	void* m_ID_name;					// Идентификатор типа

	static float DIST_AGRESSIVE_ON;		// Дистанция получения приказа агрессии
	static float DIST_AGRESSIVE_OFF;	// Дистанция возврата обратно в лагерь
	static float DIST_LOST_TARGET;		// Дистанция потери интересп к цели

public:

	static std::list<Unit*> unit_List;

	virt void EscapeToSpawn();									// Возвратиться на спавн
	virt void SetAgro(bool agro);								// Заагрить
	virt bool GetAgressive() const;								// Агрессивный
	virt bool GetAgro() const;									// Заагрился и бежит за целью
	virt bool GetIsEscape() const;								// Возвращяется ли на точку спавна
	virt vec2f GetSpawnPoint() const;							// Точка спавна
	
	virt void Attack(Unit* attacked);							// Начинаем анимацию атаки
	virt void AttackColdowner();								// Перезаряжаем атаку
	virt void AttackDealDamage(Unit* damaged);					// Наносим урон
	virt float GetAttackColdown() const;						// Время задержки между атаками
	virt int GetAttackDamage() const;							// Количество урона наносимого автоатакой
	virt float GetAttackDist() const;							// Дальность атаки
	virt bool GetIsAttackDelay() const;							// Если уже замахнулись то проводим атаку до конца
	virt void AttackDelay();									// Активируем замах

	virt void RestoreHp(int restore);							// Восстановить здоровье на restore ед.
	virt void RestoreMP(int restore);							// Восстановить ману на restore ед.
	virt void Revive(vec2f position, uint HP, uint MP);			// Воскресить с процентом здоровья и маны в указанной точке
	virt void Revive(vec2f position);							// Воскресить с полным здоровьем и маной

	virt void SetHpMax(uint hp);								// Изменить максимальное значение здоровья
	virt void SetMpMax(uint mp);								// Изменить максимальное значение маны
	virt void SetHp(uint hp);									// Изменить текущее значение здоровья
	virt void SetMp(uint mp);									// Изменить текущее значение здоровья
	virt void SetSpeed(float speed);							// Изменить скорость перемещения
	virt void SetState(const uint state);						// Изменить состояние
	virt void Corpse();											// Разлагать труп

	virt int GetHpMax() const;									// Максимальный запас здоровья
	virt int GetMpMax() const;									// Максимальный запас маны
	virt int GetHp() const;										// Здоровье текущее
	virt int GetMp() const;										// Мана текущее
	virt enum STATE GetState() const;							// Состояние действий
	virt float GetMoveSpeed() const;							// Скорость перемещения
	virt bool GetIsLife() const;								// Живой
	virt float GetCorpseTimer() const;							// Труп закончил разлагаться
	virt void* GetIdName();										// Идентификатор типа
	virt void AnimationPlay(void* animID);						// Воспроизводить анимацию

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
