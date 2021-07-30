#include "Food.h"

Food::Food(int x, int y)
{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(16);
	setHeight(16);
	setRealCollisionRect(16, 16);
	getRigidBody().setMass(5);
	getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
}

Food::~Food()
{
}

void Food::draw()
{
}

void Food::update()
{
}

void Food::clean()
{
}

void Food::collision(DisplayObject* obj)
{
}
