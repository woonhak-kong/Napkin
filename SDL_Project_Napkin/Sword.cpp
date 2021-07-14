#include "Sword.h"

Sword::Sword(int power, int reach, int maxDurability) :
	m_attackPower(power),
	m_reach(reach),
	m_durability(maxDurability),
	m_maxDurability(maxDurability)
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
