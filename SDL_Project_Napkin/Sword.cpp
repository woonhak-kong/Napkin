#include "Sword.h"

Sword::Sword(int power, int reach, int maxDurability, SwordType type) :
	m_attackPower(power),
	m_reach(reach),
	m_durability(maxDurability),
	m_maxDurability(maxDurability),
	m_swordType(type)
{
}

void Sword::draw()
{
	PhysicsObject::draw();
}

void Sword::update()
{
	PhysicsObject::update();
}

void Sword::clean()
{
}

void Sword::collision(DisplayObject* obj)
{
}

int Sword::getPower() const
{
	return m_attackPower;
}

int Sword::getReach() const
{
	return m_reach;
}

int Sword::getDurability() const
{
	return m_durability;
}

SwordType Sword::getSwordType() const
{
	return m_swordType;
}

void Sword::setDurability(int value)
{
	if( value > m_maxDurability)
	{
		m_durability = m_maxDurability;
	}
	m_durability = value;
}
