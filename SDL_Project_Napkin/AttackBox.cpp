#include "AttackBox.h"

#include <iostream>

#include "Camera.h"
#include "Config.h"
#include "Scene.h"
#include "TextureManager.h"

AttackBox::AttackBox(SDL_Rect rect, glm::vec2 velocity, int distance, GameObjectType attackType, int power)
{
	getTransform().getPosition().x = rect.x;
	getTransform().getPosition().y = rect.y;
	setWidth(rect.w);
	setHeight(rect.h);
	getRigidBody().getVelocity() = velocity;
	m_distance4Delete = distance;
	m_startingPoint = rect.x;
	setType(attackType);
	setRealCollisionRect(rect.w, rect.h);
	m_power = power;
	m_isDeleted = false;
}

AttackBox::~AttackBox()
{
}

void AttackBox::draw()
{
	if (Config::SHOWING_DEBUG)
	{
		const SDL_Color redColor = { 255, 0, 0, 255 };
		const SDL_Rect collisionBox{ getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight() };
		TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, redColor);
	}
}

void AttackBox::update()
{
	getTransform().getPosition() += getRigidBody().getVelocity();
	if (abs(m_startingPoint - getTransform().getPosition().x) > m_distance4Delete)
	{
		deleteAttackBox();
	}
}

void AttackBox::clean()
{
}

void AttackBox::collision(DisplayObject* obj)
{

}

int AttackBox::getAttackPower() const
{
	return m_power;
}

void AttackBox::deleteAttackBox()
{
	if (!m_isDeleted)
	{
		getParent()->addChildRemoving(this);
		m_isDeleted = true;
	}
}
