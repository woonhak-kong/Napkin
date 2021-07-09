#include "Boss1.h"

#include "Camera.h"
#include "EnemyHumanAI.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "TextureID.h"
#include "TextureManager.h"

Boss1::Boss1(const LoaderParams& loader):
	Character(loader)
{
	setAnimation(TextureManager::Instance().getAnimation(TextureID::BOSS1));

	// todo make it automatic
	setType(GameObjectType::ENEMY);
	setAttackType(GameObjectType::ENEMY_ATTACK);
	setGameAI(new EnemyHumanAI(this));
	//////////////////////////////////////
	///
	setAttackSpeed(2);
	setAttackReach(100);
}

void Boss1::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_IDLE), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, true);
			break;
		case CharacterState::ATTACK:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_ATTACK1), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, true,  [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							this->makingAttackCollisionBox();
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
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_RUN), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::JUMP:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_JUMP), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::FALL:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_FALL), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::HIT:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_HIT), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, true,  [&](CallbackType type) ->  void { this->setIsHit(false); });
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_DEAD), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
	}
}

void Boss1::update()
{
	Character::update();
	getGameAI()->update();
}

void Boss1::clean()
{
}

void Boss1::collision(DisplayObject* obj)
{
}

void Boss1::hit()
{
}

void Boss1::die()
{
}
