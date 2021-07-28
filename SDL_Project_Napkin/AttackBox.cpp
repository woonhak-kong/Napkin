#include "AttackBox.h"

#include <iostream>

#include "Camera.h"
#include "Config.h"
#include "Scene.h"
#include "TextureID.h"
#include "TextureManager.h"

AttackBox::AttackBox(SDL_Rect rect, glm::vec2 velocity, int distance, GameObjectType attackType, int power, SDL_RendererFlip flip, SwordType type /* = SwordType::NONE*/)
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
	m_type = type;
	m_flip = flip;
	setAnimation(TextureManager::Instance().getAnimation(TextureID::ATTACK_BOX));
}

AttackBox::~AttackBox()
{
}

void AttackBox::draw()
{
	SDL_RendererFlip tmp;
	if (Config::SHOWING_DEBUG)
	{
		const SDL_Color redColor = { 255, 0, 0, 255 };
		const SDL_Rect collisionBox{ getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight() };
		TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, redColor);
	}

	switch (m_type)
	{

		case SwordType::NONE:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::SLASH_BASIC), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 0, m_flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							break;
						case CallbackType::ANIMATION_END:
							this->deleteAttackBox();
							break;
						default:
							break;
					}
				});
			break;
		case SwordType::BASIC_SWORD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::SLASH_BASIC), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, m_flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							break;
						case CallbackType::ANIMATION_END:
							this->deleteAttackBox();
							break;
						default:
							break;
					}
				});
			break;
		case SwordType::FIRE_SWORD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::SLASH_FIRE), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 4.f, 0.0f, 255, m_flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							break;
						case CallbackType::ANIMATION_END:
							this->deleteAttackBox();
							break;
						default:
							break;
					}
				});
			break;
		case SwordType::DARK_SWORD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::SLASH_DARK), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, m_flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							break;
						case CallbackType::ANIMATION_END:
							this->deleteAttackBox();
							break;
						default:
							break;
					}
				});
			break;
		case SwordType::LASER_SWORD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::SLASH_LASER), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 4.f, 0.0f, 255, m_flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							break;
						case CallbackType::ANIMATION_END:
							this->deleteAttackBox();
							break;
						default:
							break;
					}
				});
			break;
		case SwordType::SHOT:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_RANGE_SHOT), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, m_flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							break;
						case CallbackType::ANIMATION_END:
							this->deleteAttackBox();
							break;
						default:
							break;
					}
				});
			break;

	}
}

void AttackBox::update()
{
	/*getTransform().getPosition() += getRigidBody().getVelocity();
	if (abs(m_startingPoint - getTransform().getPosition().x) > m_distance4Delete)
	{
		deleteAttackBox();
	}*/
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
