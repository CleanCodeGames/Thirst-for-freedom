#include "Sun.h"


Sun::Sun(vec2f position, vec2f size)
{
	this->SetParam(position, size, true);
	m_Sun.SetParam(position, size, true);
	this->SetTexture(texture->sun[0]);
	m_Sun.SetTexture(texture->sun[1]);
	ambience_List.push_back(this);
	ambience_List.push_back(&m_Sun);
}

void Sun::Update()
{
	this->Rotate(0.03f*time);
	m_Sun.Rotate(-0.03f*time);
}


Sun::~Sun(void)
{
}
