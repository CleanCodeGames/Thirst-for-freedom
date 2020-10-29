#include "Sprite.h"



std::list<Sprite*> Sprite :: ambience_List;
std::list<Sprite*> Sprite :: ui_List;

inl void Sprite::Rotate(float r)				{ m_Sprite.rotate(r);				}

inl void Sprite::SetRotation(float a)			{ m_Sprite.setRotation(a);			}

inl void Sprite::SetTextureRect(sf::IntRect r)	{ m_Sprite.setTextureRect(r);		}

inl void Sprite::SetPos(vec2f p)				{ m_Sprite.setPosition(p);			}

inl void Sprite::SetOrigin(vec2f o)				{ m_Sprite.setOrigin(o);			}

inl void Sprite::Move(vec2f s)					{ m_Sprite.move(s);					}

inl void Sprite::SetSize(vec2f s)				{ m_Sprite.setSize(s);				}

inl void Sprite::SetColor(sf::Color c)			{ m_Sprite.setFillColor(c);			}

void Sprite::SetAng(float a)					{ m_Angle = a;						}

inl sf::Color Sprite::GetColor() const			{ return m_Sprite.getFillColor();	}

inl vec2f Sprite::GetPos() const				{ return m_Sprite.getPosition();	}

inl vec2f Sprite::GetSize() const				{ return m_Sprite.getSize();		}

inl float Sprite::GetRotation() const			{ return m_Sprite.getRotation();	}

inl void Sprite::SetTexture(sf::Texture& t)		{ m_Sprite.setTexture(&t);			}

float Sprite::GetAng() const					{ return m_Angle;					}

sf::RectangleShape& Sprite::GetSprite()			{ return m_Sprite;					}

float Sprite :: GetDistPos(vec2f pos)
{
	return sqrt(pow((GetPos().x - pos.x),2) + pow((GetPos().y - pos.y),2));
}

void Sprite::MoveToAngle(float speed)
{
	float sx = cosf(m_Angle * PI / 180.f) * (speed * time);
	float sy = sinf(m_Angle * PI / 180.f) * (speed * time);
	m_Sprite.move(sx,sy); 
}

void Sprite::MoveToAngle(float speed, float angle)
{
	float sx = cosf(angle * PI / 180.f) * (speed * time);
	float sy = sinf(angle * PI / 180.f) * (speed * time);
	m_Sprite.move(sx,sy); 
}

float Sprite::GetAngPos(vec2f p) 
{ 
	return atan2f(p.y - GetPos().y, p.x - GetPos().x) * DEG; 
}

sf::FloatRect Sprite::GetRect() 
{ 
	return sf::FloatRect(GetPos().x-GetSize().x/2,GetPos().y-GetSize().y/2,GetSize().x,GetSize().y); 
}

inl bool Sprite::InterRect(sf::FloatRect& r) 
{
	if(GetRect().intersects(r)) 
		return true;
	else return false;
}

inl bool Sprite::Contains (vec2f p) 
{
	if(GetRect().contains(p)) 
		return true;
	else return false;
}

inl void Sprite::SetScale(vec2f scale)
{
	m_Sprite.setScale(scale.x, scale.y);
}

void Sprite :: Draw()
{
	if(InterRect(GetVisibleCam()))
		window->draw(m_Sprite);
}

Sprite::Sprite(vec2f position, vec2f size, bool isOrigin)
{
	m_Sprite.setSize(size*screen_1);
	m_Sprite.setPosition(position*screen_1);
	if(isOrigin) m_Sprite.setOrigin(m_Sprite.getSize()/2.f);
	m_Angle = 0;
}

Sprite::Sprite()
{
	m_Sprite.setSize(vec2f(0,0));
	m_Sprite.setPosition(vec2f(0,0));
	m_Angle = 0;
}

void Sprite::SetParam(vec2f position, vec2f size, bool isOrigin)
{
	m_Sprite.setSize(size*screen_1);
	m_Sprite.setPosition(position*screen_1);
	if(isOrigin) m_Sprite.setOrigin(m_Sprite.getSize()/2.f);
}

