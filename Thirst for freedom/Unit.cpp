#include "Unit.h"

std::list<Unit*> Unit :: unit_List;
std::list<Missle*> Missle :: missle_List;
float Unit :: DIST_AGRESSIVE_ON;
float Unit :: DIST_AGRESSIVE_OFF;
float Unit :: DIST_LOST_TARGET;


Unit :: Unit(vec2f position, vec2f size, void* name_ID) 
	: Sprite(position, size, true)
{
	m_ID_name = name_ID;

	// Arnold
	#pragma region

		if(m_ID_name == "Arnold")
		{
			m_Hit_Point_Max				= 150;
			m_Mana_Point_Max			= 100;
			m_Speed_Movement_Default	= 200;
			m_Attack_Dist				= size.y*1.5f;
			m_Attack_Damage				= 25;
			m_Is_Melee					= true;
			m_Attack_Coldown_CONST		= 1800;
			m_Attack_Delay_Time_CONST	= 300;
			m_Is_Escape					= false;
			SetTexture(texture->arnold);
			SetTextureRect(sf::IntRect(24,0,24,32));
		}

	#pragma endregion

	// Crussader
	#pragma region

		if(m_ID_name == "Crussader")
		{
			m_Hit_Point_Max				= 70;
			m_Mana_Point_Max			= 0;
			m_Speed_Movement_Default	= 85;
			m_Attack_Dist				= size.y*1.5f;
			m_Attack_Damage				= 10;
			m_Is_Melee					= true;
			m_Attack_Coldown_CONST		= 2200;
			m_Attack_Delay_Time_CONST	= 300;
			m_Is_Escape					= true;
			SetTexture(texture->crussader);
			SetTextureRect(sf::IntRect(24,0,24,32));
		}

	#pragma endregion 

	// Tower
	#pragma region

		if(m_ID_name == "Tower")
		{
			m_Hit_Point_Max				= 55;
			m_Mana_Point_Max			= 0;
			m_Speed_Movement_Default	= 0;
			m_Attack_Dist				= 30;
			m_Attack_Damage				= 7;
			m_Is_Melee					= false;
			m_Attack_Coldown_CONST		= 2000;
			m_Attack_Delay_Time_CONST	= 300;
			m_Is_Escape					= true;
			SetTexture(texture->tower);
			SetTextureRect(sf::IntRect(24,0,24,32));
		}

	#pragma endregion

	// Soul Collector
	#pragma region

		if(m_ID_name == "SoulCollector")
		{
			m_Hit_Point_Max				= 70;
			m_Mana_Point_Max			= 90;
			m_Speed_Movement_Default	= 120;
			m_Attack_Dist				= 6;
			m_Attack_Damage				= 10;
			m_Is_Melee					= true;
			m_Attack_Coldown_CONST		= 2200;
			m_Attack_Delay_Time_CONST	= 300;
			m_Is_Escape					= true;
			SetTexture(texture->soul_Collector);
			SetTextureRect(sf::IntRect(24,0,24,32));
		}

	#pragma endregion 
	
	// Moomie
	#pragma region

		if(m_ID_name == "Moomie")
		{
			m_Hit_Point_Max				= 55;
			m_Mana_Point_Max			= 30;
			m_Speed_Movement_Default	= 70;
			m_Attack_Dist				= 20;
			m_Attack_Damage				= 3;
			m_Is_Melee					= false;
			m_Attack_Coldown_CONST		= 200;
			m_Attack_Delay_Time_CONST	= 125;
			m_Is_Escape					= false;
			SetTexture(texture->moomie);
			SetTextureRect(sf::IntRect(24,0,24,32));
		}

	#pragma endregion

	m_Is_Agro = false;
	m_Is_Agressive = true;
	m_Spawn_Point = GetPos();

	m_Speed_Movement		=(m_Speed_Movement_Default / 10000.f) * screen_1;
	m_Attack_Coldown		= m_Attack_Coldown_CONST;
	m_Attack_Delay_Time		= m_Attack_Delay_Time_CONST;
	m_Attack_Dist			*= screen_1;
	m_Hit_Point				= m_Hit_Point_Max;
	m_Mana_Point			= m_Mana_Point_Max;
	m_Is_Attack_Delay		= false;
	m_Is_Life				= true;
	m_State					= STAND;
	m_Corpse_Timer			= 20000.f;

	unit_List.push_back(this);
}

void Unit :: EscapeToSpawn()
{
	if(GetDistPos(m_Spawn_Point) > screen_1)
	{
		MoveToAngle(m_Speed_Movement, GetAngPos(m_Spawn_Point));
		m_Hit_Point = m_Hit_Point_Max;
		m_Mana_Point = m_Mana_Point_Max;
	}
	else
	{
		m_State = STAND;
		m_Is_Agro = false;
	}
}

vec2f Unit :: GetSpawnPoint() const { return m_Spawn_Point; }

bool Unit :: GetAgro() const { return m_Is_Agro; }

bool Unit :: GetAgressive() const { return m_Is_Agressive; }

void Unit :: SetAgro(bool agro) { m_Is_Agro = agro; }

bool Unit :: GetIsEscape() const { return m_Is_Escape; }

void Unit :: AttackDealDamage(Unit* damaged)
{
	damaged->m_Hit_Point -= m_Attack_Damage;							// Наносим урон

	if(damaged->m_Hit_Point <= 0)
	{
		damaged->m_Hit_Point = 0;										// Убиваем цель
		damaged->m_Is_Life = false;
		damaged->m_Is_Attack_Delay = false;								// Совершили атаку до конца
		damaged->m_Attack_Delay_Time = m_Attack_Delay_Time_CONST;		// Обновляем счётчик замаха
		damaged->m_Attack_Coldown = m_Attack_Coldown_CONST;				// Обновляем перезарядку атаки
		damaged->SetColor(sf::Color(255,255,255));
	}
}

void Unit :: RestoreHp(int restore)
{
	m_Hit_Point += restore;
	if(m_Hit_Point > m_Hit_Point_Max)
		m_Hit_Point = m_Hit_Point_Max;
}

void Unit :: RestoreMP(int restore)
{
	m_Mana_Point += restore;
	if(m_Mana_Point > m_Mana_Point_Max)
		m_Mana_Point = m_Mana_Point_Max;
}

void Unit :: Revive(vec2f position, uint HP, uint MP)
{
	if(!m_Is_Life)
	{
		SetPos(position);
		m_Hit_Point = m_Hit_Point_Max / 100 * HP;
		m_Mana_Point = m_Mana_Point_Max / 100 * MP;
		m_Is_Life = true;
	}
}

void Unit :: Revive(vec2f position)
{
	if(!m_Is_Life)
	{
		SetPos(position);
		m_Hit_Point = m_Hit_Point_Max;
		m_Mana_Point = m_Mana_Point_Max;
		m_Is_Life = true;
	}
}

void Unit :: AttackColdowner() {
	if(m_Attack_Coldown >= 0) 
		m_Attack_Coldown -= time;
}

void Unit :: AttackDelay() {
	m_Is_Attack_Delay = true;
}

void Unit :: Attack(Unit* attacked)
{
	if(m_Attack_Coldown <= 0)										// Если автоатака перезарядилась
	{
		if(m_Attack_Delay_Time >= 0) m_Attack_Delay_Time -= time;	// Считаем время замаха

		SetColor(sf::Color::Red);

		if(m_Attack_Delay_Time <= 0)									// Еслитаймер замаха истёк
		{
			if(m_Is_Melee) 
				AttackDealDamage(attacked);
			else
			{
				if(m_ID_name == "Tower") 
					Missle::missle_List.push_back(new Missle(vec2f(3,3), this, attacked, 320, texture->missle_Tower));
				if(m_ID_name == "Moomie") 
					Missle::missle_List.push_back(new Missle(vec2f(3,3), this, attacked, 200, texture->missle_Moomie));
			}
			SetColor(sf::Color(255,255,255));
			m_Is_Attack_Delay = false;								// Совершили атаку до конца
			m_Attack_Delay_Time = m_Attack_Delay_Time_CONST;		// Обновляем счётчик замаха
			m_Attack_Coldown = m_Attack_Coldown_CONST;				// Обновляем перезарядку атаки
		}

		if(!attacked->GetIsLife())
		{
			SetColor(sf::Color(255,255,255));
			m_Is_Attack_Delay = false;								// Совершили атаку до конца
			m_Attack_Delay_Time = m_Attack_Delay_Time_CONST;		// Обновляем счётчик замаха
			m_Attack_Coldown = m_Attack_Coldown_CONST;				// Обновляем перезарядку атаки
		}
	}
}

void Unit :: SetSpeed(float speed) {
	m_Speed_Movement = (speed / 10000.f) * screen_1;
}

void Unit :: SetHp(uint hp) {
	m_Hit_Point = hp;
	if(m_Hit_Point_Max < m_Hit_Point)
		m_Hit_Point = m_Hit_Point_Max;
}

void Unit :: SetMp(uint mp) {
	m_Mana_Point = mp;
	if(m_Mana_Point_Max < m_Mana_Point)
		m_Mana_Point = m_Mana_Point_Max;
}

void Unit :: SetHpMax(uint hp) {
	m_Hit_Point_Max = hp; 
}

void Unit :: SetMpMax(uint mp) { 
	m_Mana_Point_Max = mp; 
}

void Unit :: SetState(const uint state) {
	m_State = (STATE)state;
}

void Unit :: Corpse()
{
	const static float timer = m_Corpse_Timer;
	m_Corpse_Timer -= time;
	if(m_Corpse_Timer < 0.f) m_Corpse_Timer = 0.f;
	SetColor(sf::Color(255,255,255, sf::Uint8(m_Corpse_Timer / timer * 255)));
}

void Unit :: AnimationPlay(void* animID)
{
	if(animID == "Stand") SetTextureRect(sf::IntRect(24,0,24,32));
	else
	{
		if(m_Frame_Timer > 0) {
			m_Frame_Timer -= time;
		}
		else {
				m_Frame_Timer = 125.f;
				if(m_Frame != 2) m_Frame++;
				else m_Frame = 0;

				if(animID == "MoveUp")		SetTextureRect(sf::IntRect(m_Frame*24,96,24,32));
				if(animID == "MoveDown")	SetTextureRect(sf::IntRect(m_Frame*24,0,24,32));
				if(animID == "MoveLeft")	SetTextureRect(sf::IntRect(m_Frame*24,32,24,32));
				if(animID == "MoveRight")	SetTextureRect(sf::IntRect(m_Frame*24,64,24,32));
		}
	}
}

float Unit :: GetCorpseTimer() const
{
	return m_Corpse_Timer;
}

bool Unit :: GetIsAttackDelay() const			{ return m_Is_Attack_Delay; }

int Unit :: GetHpMax() const					{ return m_Hit_Point_Max; }

int Unit :: GetMpMax() const					{ return m_Mana_Point_Max; }

int Unit :: GetHp() const						{ return m_Hit_Point; }

int Unit :: GetMp() const						{ return m_Mana_Point; }

bool Unit :: GetIsLife() const					{ return m_Is_Life; }

float Unit :: GetMoveSpeed() const				{ return m_Speed_Movement; }

float Unit :: GetAttackDist() const				{ return m_Attack_Dist; }

int Unit :: GetAttackDamage() const				{ return m_Attack_Damage; }

float Unit :: GetAttackColdown() const			{ return m_Attack_Coldown; }

enum Unit :: STATE Unit :: GetState() const		{ return m_State; }

void* Unit :: GetIdName()						{ return m_ID_name; }



Missle :: Missle(vec2f size, Unit* owner, Unit* target, float speed, PNG& png) 
	: Sprite(vec2f(0,0), size, true)
{
	m_Unit_Target = target;
	m_Unit_Owner = owner;
	m_Is_Life = true;
	m_Misle_Speed = (speed / 10000.f) * screen_1;
	SetPos(vec2f(m_Unit_Owner->GetPos().x, m_Unit_Owner->GetPos().y - m_Unit_Owner->GetSize().y / 3.f));
	m2.SetParam(GetPos()/screen_1, size, true);
	SetTexture(png);
	m2.SetTexture(png);
	SetTextureRect(sf::IntRect(0,0,64,64));
	m2.SetTextureRect(sf::IntRect(64,0,64,64));
}

void Missle :: Update()
{
	MoveToAngle(m_Misle_Speed, GetAngPos(m_Unit_Target->GetPos()));
	m2.MoveToAngle(m_Misle_Speed, GetAngPos(m_Unit_Target->GetPos()));
	Rotate(0.3*time);
	m2.Rotate(-0.3*time);
	if(GetDistPos(m_Unit_Target->GetPos()) < screen_1 * 2)
	{
		m_Unit_Owner->AttackDealDamage(m_Unit_Target);
		m_Is_Life = false;
	}
}

bool Missle :: GetIsLife() const { return m_Is_Life; }

Sprite Missle :: GetSpriteM2() { return m2; }

void Missle :: Draw()
{
	if(InterRect(GetVisibleCam()))
	{
		window->draw(m_Sprite);
		window->draw(m2.GetSprite());
	}
}