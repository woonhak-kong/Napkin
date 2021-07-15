#include "Sword.h"

#include "Camera.h"
#include "TextureID.h"
#include "TextureManager.h"

Sword::Sword(int x, int y, SwordType type) :
	m_swordType(type)
{
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(50);
	setHeight(50);
	setRealCollisionRect(50, 50);
	getRigidBody().setMass(5);
	getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
	switch (m_swordType)
	{
		case SwordType::BASIC_SWORD:
			m_reach = 10;
			m_attackSpeed = 0.5;
			m_attackPower = 30;
			break;
		case SwordType::FIRE_SWORD:
			m_reach = 30;
			m_attackSpeed = 1;
			m_attackPower = 100;
			break;
		case SwordType::LASER_SWORD:
			m_reach = 200;
			m_attackSpeed = 2;
			m_attackPower = 50;
			break;
		case SwordType::DARK_SWORD:
			m_reach = 100;
			m_attackSpeed = 1.5;
			m_attackPower = 80;
			break;

	}
}

void Sword::draw()
{
	PhysicsObject::draw();
	switch (m_swordType)
	{
		case SwordType::BASIC_SWORD:
			TextureManager::Instance().draw(TextureID::BASIC_SWORD, getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight());
			break;
		case SwordType::FIRE_SWORD:
			TextureManager::Instance().draw(TextureID::FIRE_SWORD, getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight());
			break;
		case SwordType::LASER_SWORD:
			TextureManager::Instance().draw(TextureID::LASER_SWORD, getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight());
			break;
		case SwordType::DARK_SWORD:
			TextureManager::Instance().draw(TextureID::DARK_SWORD, getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight());
			break;

	}
}

void Sword::drawUi()
{
	//PhysicsObject::draw();
	switch (m_swordType)
	{
		case SwordType::BASIC_SWORD:
			TextureManager::Instance().draw(TextureID::BASIC_SWORD, getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getHeight());
			break;
		case SwordType::FIRE_SWORD:
			TextureManager::Instance().draw(TextureID::FIRE_SWORD, getTransform().getPosition().x , getTransform().getPosition().y , getWidth(), getHeight());
			break;
		case SwordType::LASER_SWORD:
			TextureManager::Instance().draw(TextureID::LASER_SWORD, getTransform().getPosition().x , getTransform().getPosition().y , getWidth(), getHeight());
			break;
		case SwordType::DARK_SWORD:
			TextureManager::Instance().draw(TextureID::DARK_SWORD, getTransform().getPosition().x , getTransform().getPosition().y , getWidth(), getHeight());
			break;

	}
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

float Sword::getAttackSpeed() const
{
	return m_attackSpeed;
}

int Sword::getPower() const
{
	return m_attackPower;
}

int Sword::getReach() const
{
	return m_reach;
}

int Sword::getDurability() const
{
	return m_durability;
}

SwordType Sword::getSwordType() const
{
	return m_swordType;
}

void Sword::setDurability(int value)
{
	if( value > m_maxDurability)
	{
		m_durability = m_maxDurability;
	}
	m_durability = value;
}
