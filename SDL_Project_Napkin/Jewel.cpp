#include "Jewel.h"
#include "Camera.h"
#include <iostream>
#include "TextureManager.h"

Jewel::Jewel(int x, int y) 

{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(40);
	setHeight(40);
	setRealCollisionRect(32, 32);
	getRigidBody().setMass(5);
	getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
	int velocityX = (rand() % 500) + (-(rand() % 500));
	std::cout << velocityX << std::endl;
	getRigidBody().getVelocity().x = velocityX;

	setType(GameObjectType::JEWEL);

	TextureManager::Instance().load("assets/objects/Jewel.png", "Jewel");

	m_currentPosition = m_JewelPosition[rand() % 64];
}


Jewel::~Jewel()
{

}

void Jewel::draw()
{
	PhysicsObject::draw();


	TextureManager::Instance().draw("Jewel", m_currentPosition, getTransform(), getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition()
		.y - Camera::Instance().getPosition().y, getWidth(), getHeight());

}

void Jewel::update()
{
	PhysicsObject::update();
	if (isOnGround())
	{
		getRigidBody().getVelocity() = { 0,0 };
	}
}

void Jewel::clean()
{

}


void Jewel::collision(DisplayObject* obj)
{

}


