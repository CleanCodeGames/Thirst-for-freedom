#include "Arnold.h"

Arnold::Arnold(vec2f position, vec2f size, void* name_ID) :
	Unit(position, size, name_ID)
{
	
	#pragma region

	// Арнольд

	m_Ico_Arnold.SetParam(vec2f(0,0), vec2f(8.f,8.f), true);
	m_Ico_Arnold.SetTexture(texture->ico_Arnold);

	m_Bar_HP_Arnold.SetParam(vec2f(0,0), vec2f(24, 8), true);
	m_Bar_HP_Arnold.SetTexture(texture->hp_bar);

	m_Bar_Energy_Arnold.SetParam(vec2f(0,0), vec2f(24,2), true);
	m_Bar_Energy_Arnold.SetTexture(texture->energy_bar);

	m_Indicator_HP_Arnold.SetParam(vec2f(0,0), vec2f(24,4), false);
	m_Indicator_HP_Arnold.SetColor(sf::Color(255,75,75,150));

	m_Indicator_MP_Arnold.SetParam(vec2f(0,0), vec2f(24,4), false);
	m_Indicator_MP_Arnold.SetColor(sf::Color(125,125,255,150));

	m_Indicator_Energy_Arnold.SetParam(vec2f(0,0), vec2f(24,1), false);
	m_Indicator_Energy_Arnold.SetColor(sf::Color(255,255,0,150));

	m_Indicator_Coldown_Arnold.SetParam(vec2f(0,0), vec2f(24,1), false);
	m_Indicator_Coldown_Arnold.SetColor(sf::Color(0,255,0, 150));

	// Нейтральный

	m_Ico_Neutral.SetParam(vec2f(0,0), vec2f(8.f,8.f), true);
	m_Ico_Neutral.SetTexture(texture->ico_Arnold);

	m_Bar_HP_Neutral.SetParam(vec2f(0,0), vec2f(24, 8), true);
	m_Bar_HP_Neutral.SetTexture(texture->hp_bar);

	m_Indicator_HP_Neutral.SetParam(vec2f(0,0), vec2f(24,4), false);
	m_Indicator_HP_Neutral.SetColor(sf::Color(255,75,75,150));

	m_Indicator_MP_Neutral.SetParam(vec2f(0,0), vec2f(24,4), false);
	m_Indicator_MP_Neutral.SetColor(sf::Color(125,125,255,150));

	HideNeutralBar(true);

#pragma endregion Инициализация индикаторов
	
	#pragma region

	ui_List.push_back(&m_Ico_Arnold);
	ui_List.push_back(&m_Indicator_HP_Arnold);
	ui_List.push_back(&m_Indicator_MP_Arnold);
	ui_List.push_back(&m_Indicator_Energy_Arnold);
	ui_List.push_back(&m_Indicator_Coldown_Arnold);
	ui_List.push_back(&m_Bar_HP_Arnold);
	ui_List.push_back(&m_Bar_Energy_Arnold);

	ui_List.push_back(&m_Ico_Neutral);
	ui_List.push_back(&m_Indicator_MP_Neutral);
	ui_List.push_back(&m_Indicator_HP_Neutral);
	ui_List.push_back(&m_Bar_HP_Neutral);

#pragma endregion Добавление индикаторов в список UI для отрисовки

	
	m_Frame_Timer			= 125.f;
	m_Frame					= 0;
	m_Is_Move_Right			= 
	m_Is_Move_Left			= 
	m_Is_Move_Down			= 
	m_Is_Move_Up			= false;
	m_Is_Attack_Can			= false;

	m_Factor_Assitude		= 1.0f;
	m_Energy_Point_Max		= 100;
	m_Energy_Point			= m_Energy_Point_Max;
	m_Energy_Cost			= 25;
	m_Energy_Regeneration	= 8.0f;
	

	m_Target_Unit			= 0;
	m_Picked_Unit			= 0;

	// Статические поля всех юнитов
	DIST_AGRESSIVE_ON		= (30.f * screen_1);
	DIST_AGRESSIVE_OFF		= (50.f * screen_1);
	DIST_LOST_TARGET		= (60.f * screen_1);
}

void Arnold :: Update()
{
	static bool stand = true;
 	if(m_Is_Move_Left || m_Is_Move_Right || m_Is_Move_Down || m_Is_Move_Up)
	{
		if(m_Is_Life)
		{
			stand = false;

			if(m_Is_Move_Left)	AnimationPlay("MoveLeft"); else
			if(m_Is_Move_Right)	AnimationPlay("MoveRight"); else
			if(m_Is_Move_Up)	AnimationPlay("MoveUp"); else
			if(m_Is_Move_Down)	AnimationPlay("MoveDown");

			GetMoveDirection();
			MoveToAngle(m_Speed_Movement);
		}
	}
	else if(!stand) 
	{
		stand = true;
		AnimationPlay("Stand");
	}
	if(!m_Is_Life) SetRotation(180);
	else SetRotation(0);

	if(m_Attack_Coldown <= 0 && m_Is_Attack_Can)
	{
		if(m_Target_Unit != 0) 
			Attack(m_Target_Unit);
	}
	else 
	{
		m_Is_Attack_Can = false;
		AttackColdowner();
	}

	EnergyRegeneration();
	MobAgro();
	UpdateCamera();
}

void Arnold :: EnergyRegeneration()
{
	static float timer = 0.f;
	if(m_Energy_Point < m_Energy_Point_Max) 
		timer += time;
	if(timer >= 100.f)
	{
		timer = 0.f;
		m_Energy_Point += m_Energy_Regeneration / 10.f;
		if(m_Energy_Point > m_Energy_Point_Max)
			m_Energy_Point = m_Energy_Point_Max;
	}
}

void Arnold :: MobAgro()
{
	for(std::list<Unit*>::iterator it = unit_List.begin(); it != unit_List.end();)
	{
		if(*it == this) { it++; continue; }
		Unit* m = *it;
		m->AttackColdowner();

		if(m->GetIsLife())
		{
			if(m->GetAgressive())
			{
				const float DIST = GetDistPos(m->GetPos());
				const float DIST_TO_SPAWN = m->GetDistPos(m->GetSpawnPoint());

				if(m->GetState() == STAND)
				{
					if(DIST < DIST_AGRESSIVE_ON && DIST > m->GetAttackDist())
					{
						m->SetAgro(true);
						m->SetState(FOLLOW_TO_TARGET);
					}

					if(DIST <= m->GetAttackDist())
					{
						m->SetAgro(true);
						m->SetState(ATTACK_DEAL);
					}
				}

				if(m->GetState() == FOLLOW_TO_TARGET)
				{
					m->MoveToAngle(m->GetMoveSpeed(), m->GetAngPos(GetPos()));

					if(DIST > DIST_LOST_TARGET || DIST_AGRESSIVE_OFF < DIST_TO_SPAWN)
					{
						if(m->GetIsEscape())
						{
							m->SetAgro(false);
							m->SetState(RETURN_TO_SPAWN);
						}
					}

					if(DIST < m->GetAttackDist()) 
						m->SetState(ATTACK_DEAL);
				}

				if(m->GetState() == ATTACK_DEAL)
				{
					m->Attack(this);

					if(DIST > m->GetAttackDist() && !m->GetIsAttackDelay())
						m->SetState(FOLLOW_TO_TARGET);
					else
						if(m->GetAttackColdown() <= 0)
							m->AttackDelay();
				}

				if(m->GetState() == RETURN_TO_SPAWN)
				{
					if(m->GetIsEscape() || !m_Is_Life) 
						m->EscapeToSpawn();

					if(!m->GetIsEscape() && m->GetState() == RETURN_TO_SPAWN)
						m->EscapeToSpawn();
				}

				if(!m_Is_Life) 
				{
					m->SetAgro(false);
					m->SetState(RETURN_TO_SPAWN);
				}
			}
			it++;
		}
		else
		{
			if(m->GetCorpseTimer() == 0)
			{
				if(m == m_Picked_Unit) 
				{
					m_Picked_Unit = 0;
					HideNeutralBar(true);
				}
				it = unit_List.erase(it);
				delete m;
			}
			else 
			{
				m->Corpse();
				it++;
			}
		}
	}

	for(std::list<Missle*>::iterator it = Missle :: missle_List.begin(); it != Missle :: missle_List.end();)
	{
		Missle* missle = *it;
		if(!missle->GetIsLife())
		{
			it = Missle::missle_List.erase(it); 
			delete missle;
		}
		else 
		{
			missle->Update();
			it++;
		}
	}
}

void Arnold :: Control()
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == Key::A || event.key.code == Key::Left )	m_Is_Move_Left = true;
		if(event.key.code == Key::D || event.key.code == Key::Right)	m_Is_Move_Right = true;
		if(event.key.code == Key::W || event.key.code == Key::Up)		m_Is_Move_Up = true;
		if(event.key.code == Key::S || event.key.code == Key::Down)		m_Is_Move_Down = true;

		// Тестируем урон
		if(event.key.code == Key::X) AttackDealDamage(this);
		if(event.key.code == Key::C) Revive(GetPos());
		if(event.key.code == Key::P) game_State = GAME_STATE::MAIN_MENU;
		if(event.key.code == Key::R) game_State = GAME_STATE::GAME;

		if(event.key.code == Key::Escape) window->close();
	}

	if(event.type == sf::Event::KeyReleased)
	{
		if(event.key.code == Key::A || event.key.code == Key::Left )	m_Is_Move_Left = false;
		if(event.key.code == Key::D || event.key.code == Key::Right)	m_Is_Move_Right = false;
		if(event.key.code == Key::W || event.key.code == Key::Up)		m_Is_Move_Up = false;
		if(event.key.code == Key::S || event.key.code == Key::Down)		m_Is_Move_Down = false;
	}

	if(event.type == sf::Event::MouseButtonPressed)
	{
		PickTargetUnit();
	}
}

void Arnold :: UpdateBar()
{

	#pragma region

	const vec2f& cam = camera.getCenter();
	Sprite& Ico_A = m_Ico_Arnold;
	Sprite& Ico_N = m_Ico_Neutral;

	Sprite& HP_A = m_Indicator_HP_Arnold;
	Sprite& MP_A = m_Indicator_MP_Arnold;

	Sprite& HP_N = m_Indicator_HP_Neutral;
	Sprite& MP_N = m_Indicator_MP_Neutral;

	Sprite& BAR_HP_A = m_Bar_HP_Arnold;
	Sprite& BAR_EN_A = m_Bar_Energy_Arnold;
	Sprite& EN = m_Indicator_Energy_Arnold;
	Sprite& CD = m_Indicator_Coldown_Arnold;

#pragma endregion Ссылки баров

	#pragma region

	// Крепим бар арнольда в левый верхний угол
	Ico_A.SetPos(vec2f(cam.x - (screen_X / 2) + Ico_A.GetSize().x, cam.y - (screen_Y / 2) + Ico_A.GetSize().y));
	BAR_HP_A.SetPos(vec2f(Ico_A.GetPos().x + Ico_A.GetSize().x*2, Ico_A.GetPos().y));
	BAR_EN_A.SetPos(vec2f(BAR_HP_A.GetPos().x, BAR_HP_A.GetPos().y + (BAR_EN_A.GetSize().y / 2.f) + (BAR_HP_A.GetSize().y / 2.f) ));

	// Крепим индикаторы енергии и перезарядки атаки
	EN.SetPos(vec2f(BAR_EN_A.GetPos().x - BAR_EN_A.GetSize().x / 2.f, BAR_EN_A.GetPos().y - EN.GetSize().y));
	CD.SetPos(vec2f(BAR_EN_A.GetPos().x - BAR_EN_A.GetSize().x / 2.f, BAR_EN_A.GetPos().y));

	// Крепим индикаторы здоровья и маны на свои места
	HP_A.SetPos(vec2f(Ico_A.GetPos().x + Ico_A.GetSize().x * 2 - HP_A.GetSize().x / 2, Ico_A.GetPos().y - HP_A.GetSize().y / 2 - HP_A.GetSize().y / 2));
	MP_A.SetPos(vec2f(Ico_A.GetPos().x + Ico_A.GetSize().x * 2 - MP_A.GetSize().x / 2, Ico_A.GetPos().y + MP_A.GetSize().y / 2 - MP_A.GetSize().y / 2));
	
	// Крепим бар врага в правый верхний угол
	Ico_N.SetPos(vec2f(cam.x + (screen_X / 2) - Ico_N.GetSize().x, cam.y - (screen_Y / 2) + Ico_N.GetSize().y));
	m_Bar_HP_Neutral.SetPos(vec2f(Ico_N.GetPos().x - Ico_N.GetSize().x*2, Ico_N.GetPos().y));

	// Крепим индикаторы здоровья и маны врага на свои места
	HP_N.SetPos(vec2f(Ico_N.GetPos().x - Ico_N.GetSize().x * 2 - HP_N.GetSize().x / 2, Ico_N.GetPos().y - HP_N.GetSize().y / 2 - HP_N.GetSize().y / 2));
	MP_N.SetPos(vec2f(Ico_N.GetPos().x - Ico_N.GetSize().x * 2 - MP_N.GetSize().x / 2, Ico_N.GetPos().y + MP_N.GetSize().y / 2 - MP_N.GetSize().y / 2));

#pragma endregion Устанавливаем бар в нужную позицию
	
	// Если выбрана вражеская цель
	if(m_Picked_Unit != 0)
	{
		// Меняем размер индикатора здоровья выбранной цели
		HP_N.SetScale(vec2f(s_float(m_Picked_Unit->GetHp())/s_float(m_Picked_Unit->GetHpMax()),1));
		// Меняем размер индикатора здоровья выбранной цели
		MP_N.SetScale(vec2f(s_float(m_Picked_Unit->GetMp())/s_float(m_Picked_Unit->GetMpMax()),1));
	}
	else
	{
		HP_N.SetScale(vec2f(0,1));
		MP_N.SetScale(vec2f(0,1));
	}

	// Меняем размер индикатора здоровья Арнольда
	HP_A.SetScale(vec2f(s_float(m_Hit_Point)/s_float(m_Hit_Point_Max),1));
	// Меняем размер индикатора маны Арнольда
	MP_A.SetScale(vec2f(s_float(m_Mana_Point)/s_float(m_Mana_Point_Max),1));
	// Меняем размер индикатора енергии
	EN.SetScale(vec2f(s_float(m_Energy_Point)/s_float(m_Energy_Point_Max),1));
	// Если энергии слишком мало то красим в красный
	if(m_Energy_Point < m_Energy_Cost) EN.SetColor(sf::Color(255,0,0,150));
	else EN.SetColor(sf::Color(255,255,0,150));
	// Меняем размер индикатора перезарядки атаки
	if(m_Attack_Coldown < 0.f) 
		m_Attack_Coldown = 0.f;
	CD.SetScale(vec2f(s_float(-m_Attack_Coldown)/s_float(m_Attack_Coldown_CONST)+1,1));

}

void Arnold :: HideNeutralBar(bool hide)
{
	if(hide)
	{
		m_Ico_Neutral.SetColor(sf::Color(255,255,255,0));
		m_Bar_HP_Neutral.SetColor(sf::Color(255,255,255,0));
		m_Indicator_HP_Neutral.SetColor(sf::Color(255,75,75,0));
		m_Indicator_MP_Neutral.SetColor(sf::Color(125,125,255,0));
	}
	else
	{
		m_Ico_Neutral.SetColor(sf::Color(255,255,255,255));
		m_Bar_HP_Neutral.SetColor(sf::Color(255,255,255,255));
		m_Indicator_HP_Neutral.SetColor(sf::Color(255,75,75,150));
		m_Indicator_MP_Neutral.SetColor(sf::Color(125,125,255,150));
	}
}

void Arnold :: PickTargetUnit()
{
	if(event.key.code == sf::Mouse::Left)
	{
		for(auto u: unit_List)
			if(u->Contains(mouse_Position)) 
			{
				m_Picked_Unit = u;
				HideNeutralBar(false);
				if(u->GetIdName() == "Arnold")			m_Ico_Neutral.SetTexture(texture->ico_Arnold);
				if(u->GetIdName() == "Crussader")		m_Ico_Neutral.SetTexture(texture->ico_Crussader);
				if(u->GetIdName() == "SoulCollector")	m_Ico_Neutral.SetTexture(texture->ico_Soul_Collector);
				if(u->GetIdName() == "Moomie")			m_Ico_Neutral.SetTexture(texture->ico_Moomie);
				if(u->GetIdName() == "Tower")			m_Ico_Neutral.SetTexture(texture->ico_Tower);
				
				if(GetDistPos(u->GetPos()) <= m_Attack_Dist && u != this)
				{
					if(m_Energy_Point >= m_Energy_Cost && !m_Is_Attack_Can && u->GetIsLife())
					{
						if(m_Attack_Coldown <= 0) 
							m_Energy_Point -= m_Energy_Cost;
						if(m_Picked_Unit != this) 
						{
							m_Target_Unit = m_Picked_Unit;
							m_Is_Attack_Can = true;
						}
					}
				}
			}
	}

	if(event.key.code == sf::Mouse::Right)
	{
			m_Picked_Unit = 0;
			HideNeutralBar(true);
	}
}

float Arnold :: GetMoveDirection()
{
	if(m_Is_Move_Left && m_Is_Move_Down)	return m_Angle = 135.f;
	if(m_Is_Move_Up && m_Is_Move_Left)		return m_Angle = 225.f;
	if(m_Is_Move_Down && m_Is_Move_Right)	return m_Angle = 45.f;
	if(m_Is_Move_Right && m_Is_Move_Up)		return m_Angle = 315;

		if(m_Is_Move_Left)	return m_Angle = 180.f;
		if(m_Is_Move_Right)	return m_Angle = 0.f;
		if(m_Is_Move_Down)	return m_Angle = 90.f;
		if(m_Is_Move_Up)	return m_Angle = 270.f;

	return m_Angle;
}

void Arnold :: UpdateCamera()
{
	if(GetDistPos(camera.getCenter()) > screen_1)
	{
		float s = 0.00015f*screen_1*GetDistPos(camera.getCenter())*time;
		float sx = cosf(GetAngPos(camera.getCenter()) * PI/180.f)*s;
		float sy = sinf(GetAngPos(camera.getCenter()) * PI/180.f)*s;
		camera.move(-sx,-sy);
	}
	UpdateBar();
	window->setView(camera);
}