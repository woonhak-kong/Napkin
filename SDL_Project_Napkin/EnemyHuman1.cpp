#include "EnemyHuman1.h"

#include "AttackBox.h"
#include "CallbackType.h"
#include "Camera.h"
#include "EnemyHumanAI.h"
#include "Explosion.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "TextureID.h"
#include "TextureManager.h"

EnemyHuman1::EnemyHuman1(const LoaderParams& loader) :
	Character(loader)
{
	setAnimation(TextureManager::Instance().getAnimation(TextureID::ENEMY_HUMAN));

	// todo make it automatic
	setType(GameObjectType::ENEMY);
	setAttackType(GameObjectType::ENEMY_ATTACK);
	setGameAI(new EnemyHumanAI(this));
	//////////////////////////////////////
	///
	setAttackSpeed(2);
	setAttackReach(100);
}

EnemyHuman1::~EnemyHuman1()
{
}

void EnemyHuman1::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_IDLE), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip);
			break;
		case CharacterState::ATTACK:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_ATTACK), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip, true, [&](CallbackType type) -> void
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
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_RUN), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip);
			break;
		case CharacterState::JUMP:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_JUMP), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip);
			break;
		case CharacterState::FALL:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_FALL), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip);
			break;
		case CharacterState::HIT:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_HIT), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip, true,  [&](CallbackType type) ->  void { this->setIsHit(false); });
			break;
		case CharacterState::DEAD:

			break;
	}
}

void EnemyHuman1::update()
{
	Character::update();
	getGameAI()->update();
}

void EnemyHuman1::clean()
{

	getParent()->addChildDuringUpdating(new Explosion(getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getHeight(), ExplosionType::EXPLOSION_BIG));
}

void EnemyHuman1::collision(DisplayObject* obj)
{
	if (obj->getType() == GameObjectType::PLAYER_ATTACK)
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
	}
}

void EnemyHuman1::hit()
{
	if (!isHit())
	{
		SoundManager::Instance().playSound(SoundID::HIT);
	}
	Character::hit();
}
