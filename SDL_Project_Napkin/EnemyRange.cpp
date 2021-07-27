#include "EnemyRange.h"

#include "AttackBox.h"
#include "CallbackType.h"
#include "Camera.h"
#include "EnemyHumanAI.h"
#include "Explosion.h"
#include "Scene.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "Sword.h"
#include "TextureID.h"
#include "TextureManager.h"

EnemyRange::EnemyRange(const LoaderParams& loader) :
	Character(loader)
{
	setAnimation(TextureManager::Instance().getAnimation(TextureID::ENEMY_RANGE));

	// todo make it automatic
	setType(GameObjectType::ENEMY);
	setAttackType(GameObjectType::ENEMY_ATTACK);
	setGameAI(new EnemyHumanAI(this));
	//////////////////////////////////////
	///
	setAttackSpeed(2);
	setAttackReach(50);
	setAttackRectSize(50, 0);
	setMoveSpeed(100);
}

EnemyRange::~EnemyRange()
{
}

void EnemyRange::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_RANGE_IDLE), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::ATTACK:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_RANGE_ATTACK), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							this->makingAttackCollisionBox();
							SoundManager::Instance().playSound(SoundID::ENEMY_MELEE_ATTACK);
							break;
						case CallbackType::ANIMATION_END:
							this->setIsAttacking(false);
							break;
						default:
							break;
					}

				}, 2);
			break;
		case CharacterState::RUN:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_RANGE_RUN), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::JUMP:
			break;
		case CharacterState::FALL:
			break;
		case CharacterState::HIT:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_RANGE_HIT), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, true, [&](CallbackType type) ->  void { this->setIsHit(false); });
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_RANGE_DEAD), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							std::cout << "die call back" << std::endl;
							ScoreManager::addScore(10);
							getParent()->addChildDuringUpdating(new Explosion(getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getWidth(), ExplosionType::EXPLOSION_BIG));
							getParent()->addChildDuringUpdating(new Sword(getRealCollisionRect().x, getRealCollisionRect().y, static_cast<SwordType>(rand() % 3 + 1)));
							getParent()->addChildRemoving(this);
							break;
						default:
							break;
					}
				});

			break;
	}
}

void EnemyRange::update()
{
	Character::update();
	getGameAI()->update();
}

void EnemyRange::clean()
{
}

void EnemyRange::collision(DisplayObject* obj)
{
	if (obj->getType() == GameObjectType::PLAYER_ATTACK && !isHit())
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		//dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
		//std::cout << " aaa" << std::endl;
	}
}

void EnemyRange::hit()
{
	if (!isHit())
	{
		SoundManager::Instance().playSound(SoundID::HIT);
	}
	Character::hit();
}

void EnemyRange::die()
{
	Character::die();
}
