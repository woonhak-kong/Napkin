#include "Boss1.h"

#include "AttackBox.h"
#include "Boss1AI.h"
#include "Camera.h"
#include "Explosion.h"
#include "ExplosionType.h"
#include "MagicBall.h"
#include "Scene.h"
#include "ScoreManager.h"
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
	setGameAI(new Boss1AI(this));
	//////////////////////////////////////
	///
	setAttackSpeed(2);
	setAttackReach(100);
	setAttackRectSize(100, 0);
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
							magicAttack1();
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
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.1f, 0.0f, 255, flip, true,  [&](CallbackType type) ->  void { this->setIsHit(false); });
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation(TextureID::BOSS1_DEAD), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.4f, 0.0f, 255, flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							ScoreManager::addScore(100);
							getParent()->addChildDuringUpdating(new Explosion(getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getHeight(), ExplosionType::EXPLOSION_BIG));
							getParent()->getDoor()->setEnabled(true);
							getParent()->addChildRemoving(this);
							break;
						default:
							break;
					}
				});
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
	if (obj->getType() == GameObjectType::PLAYER_ATTACK)
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		//dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
	}
}

void Boss1::hit()
{
	if (!isHit())
	{
		SoundManager::Instance().playSound(SoundID::HIT);
	}
	Character::hit();
}

void Boss1::die()
{
	Character::die();
}

void Boss1::magicAttack1()
{
	glm::vec2 ball[8];
	ball[0] = glm::vec2(0, 1);
	ball[1] = glm::vec2(1, 0);
	ball[2] = glm::vec2(0, -1);
	ball[3] = glm::vec2(-1, 0);
	ball[4] = glm::vec2(0.5, 0.5);
	ball[5] = glm::vec2(0.5, -0.5);
	ball[6] = glm::vec2(-0.5, 0.5);
	ball[7] = glm::vec2(-0.5, -0.5);

	for (auto& vec2 : ball)
	{
		vec2 *= 100;
		vec2 = getCenterPosition() + vec2;
		//std::cout << getParent()->getPlayer()->getCenterPosition().x << ", " << getParent()->getPlayer()->getCenterPosition().y << std::endl;
		getParent()->addChildDuringUpdating(new MagicBall({ vec2.x, vec2.y}, { 0,0 },
			GameObjectType::ENEMY_ATTACK, 10, MagicBallType::BALL4, getParent()->getPlayer()));
	}


}

void Boss1::magicAttack2()
{
}
