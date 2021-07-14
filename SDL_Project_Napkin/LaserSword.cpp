#include "LaserSword.h"

LaserSword::LaserSword(int power, int reach, int maxDurability) :
Sword(power, reach, maxDurability, SwordType::LASER_SWORD)
{
}

LaserSword::~LaserSword()
{
}

void LaserSword::draw()
{
	Sword::draw();
}

void LaserSword::update()
{
	Sword::update();
}

void LaserSword::clean()
{
}

void LaserSword::collision(DisplayObject* obj)
{
}
