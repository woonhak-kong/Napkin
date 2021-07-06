#include "EnemyHuman1.h"

#include "Camera.h"
#include "EnemyHumanAI.h"
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
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip, [&]() -> void { this->setIsAttacking(false); });
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
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip, [&]() ->  void { this->setIsHit(false); });
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
}
