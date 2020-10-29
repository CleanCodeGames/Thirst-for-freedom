#pragma once
#include"System.h"

class Sprite :
	public System
{
protected:

	sf::RectangleShape m_Sprite;
	float m_Angle;

public:

	
	static std::list<Sprite*> ambience_List;
	static std::list<Sprite*> ui_List;

	virline void Rotate(float);	
	virline void SetRotation(float);	
	virline void SetTextureRect(sf::IntRect);
	virline void SetPos(vec2f);
	virline void SetOrigin(vec2f);
	virline void Move(vec2f);
	virline void SetSize(vec2f);
	virline void SetColor(sf::Color);
	virline void SetScale(vec2f scale);
	virline void SetTexture(sf::Texture&);
	virline float GetRotation() const;
	virline bool InterRect(sf::FloatRect&);	
	virline bool Contains(vec2f);
	virline sf::Color GetColor() const;
	virline vec2f GetPos() const;
	virline vec2f GetSize() const;
	virt float GetDistPos(vec2f pos);

	virt void SetAng(float);
	virt void MoveToAngle(float speed);
	virt void MoveToAngle(float speed, float angle);
	virt float GetAngPos(sf::Vector2f);
	virt float GetAng() const;	
	virt sf::RectangleShape& GetSprite();	
	virt sf::FloatRect GetRect();	
	virt void Draw();

	virt void SetParam(vec2f position, vec2f size, bool is_origin);
	Sprite(vec2f position, vec2f size, bool is_origin);
	Sprite();
};