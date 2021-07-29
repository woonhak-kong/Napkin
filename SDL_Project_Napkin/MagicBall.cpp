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
	m_pTargetPositionAtStart({ target->getCenterPosition().x, target->getCenterPosition().y })
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
			setWidth(30);
			setHeight(30);
			setRealCollisionRect(30, 30);
			getRigidBody().getVelocity() = normalize(m_pTargetPositionAtStart - getTransform().getPosition()) * 200.f;
		break;

		default:
			break;
	}
	//std::cout << m_pTargetPositionAtStart.x << ", " << m_pTargetPositionAtStart.y << std::endl;
	setAnimation(TextureManager::Instance().getAnimation(TextureID::FIRE_BALL));
}

MagicBall::~MagicBall()
{
	//std::cout << " ccc" << std::endl;
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
			TextureManager::Instance().playAnimation(getAnimation(TextureID::FIRE_BALL4), getTransform().getPosition().x - Camera::Instance().getPosition().x,
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

		default:
			break;
	}
}

void MagicBall::update()
{
	switch (m_type)
	{
		case MagicBallType::BALL1:
			// seeking
	/*glm::vec2 desired_velocity = normalize(m_pTargetPositionAtStart - getTransform().getPosition()) * 100.f;

	glm::vec2 steering = (desired_velocity - getRigidBody().getVelocity())/100.0f;

	getRigidBody().getVelocity() += steering;*/

			getRigidBody().getVelocity().y += Config::GRAVITY / 2;
			getTransform().getPosition() = getTransform().getPosition() + getRigidBody().getVelocity() * Game::Instance().getDeltaTime();
			break;

		case MagicBallType::BALL4:

			//std::cout << m_pTargetPositionAtStart.x << ", " << m_pTargetPositionAtStart.y << std::endl;
			//std::cout << getTransform().getPosition().x << ", " << getTransform().getPosition().y << std::endl;
			getTransform().getPosition() = getTransform().getPosition() + getRigidBody().getVelocity() * Game::Instance().getDeltaTime();
			break;

		default:
			break;
	}
	//std::cout << Camera::Instance().getPosition().x << std::endl;

	if (getTransform().getPosition().x > Camera::Instance().getPosition().x + Config::SCREEN_WIDTH ||
		getTransform().getPosition().x < Camera::Instance().getPosition().x ||
		getTransform().getPosition().y > Camera::Instance().getPosition().y + Config::SCREEN_HEIGHT ||
		getTransform().getPosition().y < Camera::Instance().getPosition().y)
	{
		getParent()->addChildRemoving(this);
	}

}

void MagicBall::clean()
{
}

void MagicBall::collision(DisplayObject* obj)
{
}

glm::vec2 MagicBall::normalize(glm::vec2 vec)
{
	glm::vec2 dest;
	auto x = vec.x;
	auto y = vec.y;
	auto length = (x * x) + (y * y);
	if (length > 0) {
		length = 1.0 / sqrt(length);
		dest.x = vec.x * length;
		dest.y = vec.y * length;
	}
	return dest;
}
