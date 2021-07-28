#include "MagicBall.h"

#include "Camera.h"
#include "Config.h"
#include "Game.h"
#include "TextureID.h"
#include "TextureManager.h"

MagicBall::MagicBall(glm::vec2 point, glm::vec2 velocity, GameObjectType attackType, int power, MagicBallType type, GameObject* target) :
	AttackBox({ (int)point.x,(int)point.y,0,0 }, velocity, 0, attackType, power, SDL_FLIP_NONE),
	m_type(type),
	m_pTarget(target),
	m_pTargetPositionAtStart({ target->getTransform().getPosition().x, target->getTransform().getPosition().y })
{
	switch (m_type)
	{
		case MagicBallType::BALL1:
		setWidth(16);
		setHeight(16);
		setRealCollisionRect(16, 16);
		break;
		case MagicBallType::BALL2:

		break;
		case MagicBallType::BALL3:

		break;
		case MagicBallType::BALL4:

		break;

		default:
			break;
	}

	setAnimation(TextureManager::Instance().getAnimation(TextureID::FIRE_BALL));
}

MagicBall::~MagicBall()
{
}

void MagicBall::draw()
{
	if (Config::SHOWING_DEBUG)
	{
		const SDL_Color redColor = { 255, 0, 0, 255 };
		const SDL_Rect collisionBox{ getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight() };
		TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, redColor);
	}

	switch (m_type)
	{
		case MagicBallType::BALL1:
		TextureManager::Instance().playAnimation(getAnimation(TextureID::FIRE_BALL1), getTransform().getPosition().x - Camera::Instance().getPosition().x,
			getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, SDL_FLIP_NONE, true, [&](CallbackType type) -> void
			{
				switch (type)
				{
					case CallbackType::ATTACK_BOX:
						break;
					case CallbackType::ANIMATION_END:
						//this->deleteAttackBox();
						break;
					default:
						break;
				}
			});
		break;
		case MagicBallType::BALL2:

		break;
		case MagicBallType::BALL3:

		break;
		case MagicBallType::BALL4:

		break;

		default:
			break;
	}
}

void MagicBall::update()
{
	getTransform().getPosition() = getTransform().getPosition() + getRigidBody().getVelocity() * Game::Instance().getDeltaTime();
}

void MagicBall::clean()
{
}

void MagicBall::collision(DisplayObject* obj)
{
}
