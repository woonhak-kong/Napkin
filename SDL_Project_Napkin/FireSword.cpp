#include "FireSword.h"

FireSword::FireSword(int power, int reach, int maxDurability) :
Sword(power, reach, maxDurability, SwordType::FIRE_SWORD)
{
}

FireSword::~FireSword()
{
}

void FireSword::draw()
{
	Sword::draw();
}

void FireSword::update()
{
	Sword::update();
}

void FireSword::clean()
{
}

void FireSword::collision(::DisplayObject* obj)
{
}
