#include "Food.h"

#include <iostream>

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"

Food::Food(int x, int y) :
	m_time(0)
{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(32);
	setHeight(32);
	setRealCollisionRect(32, 32);
	getRigidBody().setMass(5);
	getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
	int velocityX = (rand() % 500) + (-(rand() % 500));
	std::cout << velocityX << std::endl;
	getRigidBody().getVelocity().x = velocityX;

	setType(GameObjectType::FOOD);

	TextureManager::Instance().load("assets/objects/food.png", "food");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_foodTexturePosition.push_back(SDL_Rect({ i * 16, j * 16, 16, 16 }));
		}
	}
	m_currentPosition = m_foodTexturePosition[rand() % 64];
}

Food::~Food()
{
}

void Food::draw()
{
	PhysicsObject::draw();

	TextureManager::Instance().draw("food", m_currentPosition, getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight());
}

void Food::update()
{
	m_time += Game::Instance().getDeltaTime();
	PhysicsObject::update();
	if(isOnGround())
	{
		getRigidBody().getVelocity() = { 0,0 };
	}

	if (m_time > 10)
	{
		getParent()->addChildRemoving(this);
	}
}

void Food::clean()
{
}

void Food::collision(DisplayObject* obj)
{
}
