#include "Character.h"

#include "Camera.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Game.h"
#include "TextureManager.h"
#include "algorithm"
#include "AttackBox.h"

Character::Character(const LoaderParams& loader) :
	m_isJumping(false),
	m_isAttacking(false),
	m_isFlip(false),
	m_attackCollisionRect({0, 0, 0, 0}),
	m_moveSpeed(200),
	m_attackSpeed(1),
	m_curState(CharacterState::IDLE),
	m_attackType(GameObjectType::NONE),
	m_presentHp(loader.m_maxHp),
	m_maxHp(loader.m_maxHp),
	m_attackPower(loader.m_power),
	m_ai(nullptr)
{
	getRigidBody().setMass(5);
	getRigidBody().getVelocity() = glm::vec2(0.0f, 0.0f);
	getRigidBody().getAcceleration() = glm::vec2(0.0f, 0.0f);
	getRigidBody().setColliding(false);
	getTransform().getPosition() = glm::vec2(loader.m_x, loader.m_y);
	setRealCollisionRect(loader.m_realWidth, loader.m_realHeight);
	setWidth(loader.m_widthOfTexture);
	setHeight(loader.m_heightOfTexture);
}

void Character::draw()
{
	PhysicsObject::draw();
}

void Character::update()
{
	PhysicsObject::update();

	/*glm::vec2 previousPosition;
	glm::vec2 newPosition;*/



	// checking player is on ground
	if (isOnGround())
	{
		m_isJumping = false;
	}
	else
	{
		m_isJumping = true;
	}


	//m_setGravity();

	//// checking x axis tile collision
	//previousPosition.x = getTransform().getPosition().x;
	//newPosition.x = getTransform().getPosition().x + (getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
	//getTransform().getPosition().x = newPosition.x;
	//if (CollisionManager::checkCollideTile(this, *m_pCollisionLayers))
	//{
	//	getTransform().getPosition().x = previousPosition.x;
	//}

	//// checking y axis tile collision
	//previousPosition.y = getTransform().getPosition().y;
	//newPosition.y = getTransform().getPosition().y + (getRigidBody().getVelocity().y * Game::Instance().getDeltaTime());
	//getTransform().getPosition().y = newPosition.y;
	//if (CollisionManager::checkCollideTile(this, *m_pCollisionLayers))
	//{
	//	m_isGroundCollision ? getRigidBody().getVelocity().y = 0 : getRigidBody().getVelocity().y = 10;
	//	getTransform().getPosition().y = previousPosition.y;
	//}

	// checking direction
	if (getRigidBody().getVelocity().x > 0)
	{
		m_isFlip = false;
	}
	else if (getRigidBody().getVelocity().x < 0)
	{
		m_isFlip = true;
	}

	// checking falling
	if (m_isJumping && !m_isAttacking)
	{
		// if falling
		if (getRigidBody().getVelocity().y > 0)
		{
			m_curState = CharacterState::FALL;
		}
	}

	// setting attackColiisonRect x, y
	if (m_isFlip)
	{
		// Left Direction
		m_attackCollisionRect.x = getRealCollisionRect().x;
		m_attackCollisionRect.y = getRealCollisionRect().y;
		m_attackCollisionRect.w = getRealCollisionRect().w;
		m_attackCollisionRect.h = getRealCollisionRect().h;

	}
	else
	{
		// Right Direction
		m_attackCollisionRect.x = getRealCollisionRect().x;
		m_attackCollisionRect.y = getRealCollisionRect().y;
		m_attackCollisionRect.w = getRealCollisionRect().w;
		m_attackCollisionRect.h = getRealCollisionRect().h;
	}



	if (m_presentHp <= 0)
	{
		getParent()->addChildRemoving(this);
	}

}

float Character::getMoveSpeed() const
{
	return m_moveSpeed;
}

float Character::getAttackSpeed() const
{
	return m_attackSpeed;
}

void Character::setAttackSpeed(float speed)
{
	m_attackSpeed = speed;
}

CharacterState Character::getCurrentState() const
{
	return m_curState;
}

bool Character::isFlip() const
{
	return m_isFlip;
}

bool Character::isAttacking() const
{
	return m_isAttacking;
}

SDL_Rect Character::getAttackCollisionRect() const
{
	return m_attackCollisionRect;
}

GameAI* Character::getGameAI() const
{
	return m_ai;
}


void Character::setMoveSpeed(float speed)
{
	m_moveSpeed = speed;
}

void Character::setCurrentState(CharacterState state)
{
	m_curState = state;
}

void Character::setAttackReach(int reach)
{
	m_attackReach = reach;
}

void Character::setAttackType(GameObjectType attackType)
{
	m_attackType = attackType;
}

void Character::m_setAttackRectSize(int w, int h)
{
	m_attackCollisionRect.w = w;
	if (h == 0)
	{
		m_attackCollisionRect.h = getRealCollisionRect().h;
	}
	else
	{
		m_attackCollisionRect.h = h;
	}

}

void Character::setIsAttacking(bool attacking)
{
	m_isAttacking = attacking;
}

void Character::setGameAI(GameAI* ai)
{
	m_ai = ai;
}

void Character::takeDamage(int damage)
{
	m_presentHp = m_presentHp - damage;
}


void Character::jump()
{
	if (!m_isJumping && !m_isAttacking)
	{
		getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
		m_isJumping = true;
		m_curState = CharacterState::JUMP;
	}


}

void Character::moveToRight()
{
	if (m_isJumping)
	{
		getRigidBody().getVelocity().x = m_moveSpeed;
	}
	else
	{
		if (!m_isAttacking)
		{
			getRigidBody().getVelocity().x = m_moveSpeed;
			m_curState = CharacterState::RUN;
		}
	}

}

void Character::moveToLeft()
{
	if (m_isJumping)
	{
		getRigidBody().getVelocity().x = -m_moveSpeed;
	}
	else
	{
		if (!m_isAttacking)
		{
			getRigidBody().getVelocity().x = -m_moveSpeed;
			m_curState = CharacterState::RUN;
		}
	}
}

void Character::idle()
{
	getRigidBody().getVelocity().x = 0;
	if (!m_isJumping && !m_isAttacking)
	{
		m_curState = CharacterState::IDLE;
	}

}

void Character::attack()
{
	if (!m_isAttacking)
	{
		m_curState = CharacterState::ATTACK;
		m_isAttacking = true;
		if (!m_isJumping)
		{
			getRigidBody().getVelocity().x = 0;
		}
		m_makingAttackCollisionBox();
	}
}

void Character::hit()
{
	m_curState = CharacterState::HIT;
}

void Character::m_makingAttackCollisionBox()
{
	getParent()->addChildDuringUpdating(new AttackBox(m_attackCollisionRect, glm::vec2(m_isFlip ? getAttackSpeed() * -10 : getAttackSpeed() * 10, 0), m_attackReach, m_attackType, m_attackPower));
}
