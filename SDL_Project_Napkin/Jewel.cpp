#include "Jewel.h"
#include "Camera.h"
#include <iostream>

#include "Game.h"
#include "TextureManager.h"

Jewel::Jewel(int x, int y):
	m_time(0)
{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(30);
	setHeight(30);
	setRealCollisionRect(30, 30);
	getRigidBody().setMass(5);
	getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
	int velocityX = (rand() % 300) + (-(rand() % 300));
	//std::cout << velocityX << std::endl;
	getRigidBody().getVelocity().x = velocityX;

	setType(GameObjectType::JEWEL);

	TextureManager::Instance().load("assets/objects/Jewel.png", "Jewel");

}


Jewel::~Jewel()
{

}

void Jewel::draw()
{
	PhysicsObject::draw();


	TextureManager::Instance().draw("Jewel", getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight());

}

void Jewel::update()
{
	m_time += Game::Instance().getDeltaTime();
	PhysicsObject::update();
	if (isOnGround())
	{
		getRigidBody().getVelocity() = { 0,0 };
	}
	if (m_time > 10)
	{
		getParent()->addChildRemoving(this);
	}
}

void Jewel::clean()
{

}


void Jewel::collision(DisplayObject* obj)
{

}


