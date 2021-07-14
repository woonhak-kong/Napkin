#include "BasicSword.h"

BasicSword::BasicSword(int power, int reach, int maxDurability) :
	Sword(power, reach, maxDurability, SwordType::BASIC_SWORD)
{
}

BasicSword::~BasicSword()
{

}

void BasicSword::draw()
{
	Sword::draw();
}

void BasicSword::update()
{
	Sword::update();
}

void BasicSword::clean()
{
}

void BasicSword::collision(DisplayObject* obj)
{
}
