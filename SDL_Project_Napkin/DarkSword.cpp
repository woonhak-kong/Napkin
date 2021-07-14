#include "DarkSword.h"

DarkSword::DarkSword(int power, int reach, int maxDurability) :
Sword(power, reach, maxDurability, SwordType::DARK_SWORD)
{
}

DarkSword::~DarkSword()
{
}

void DarkSword::draw()
{
	Sword::draw();
}

void DarkSword::update()
{
	Sword::update();
}

void DarkSword::clean()
{
}

void DarkSword::collision(DisplayObject* obj)
{
}
