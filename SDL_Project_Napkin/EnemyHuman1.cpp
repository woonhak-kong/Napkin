#include "EnemyHuman1.h"

#include "AttackBox.h"
#include "CallbackType.h"
#include "Camera.h"
#include "EnemyHumanAI.h"
#include "Explosion.h"
#include "Food.h"
#include "Jewel.h"
#include "Particle.h"
#include "Scene.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "Sword.h"
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
	setAttackReach(50);
	setAttackRectSize(50, 0);
	setMoveSpeed(100);
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
			TextureManager::Instance().playAnimation(getAnimation(TextureID::ENEMY_HUMAN_DEAD), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.4f, 0.0f, 255, flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							//std::cout << "die call back" << std::endl;
							ScoreManager::addScore(10);
							getParent()->addChildDuringUpdating(new Explosion(getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getWidth(), ExplosionType::EXPLOSION_BIG));

							if(getParent()->getState() == SceneState::TUTORIAL_SCENE)
							{

							}
							else
							{
								if (rand() % 100 < 20)
								{
									getParent()->addChildDuringUpdating(new Sword(getRealCollisionRect().x, getRealCollisionRect().y, static_cast<SwordType>(rand() % 3 + 1)));
								}
							}

							for (int i = 0; i < 10; ++i)
							{
								getParent()->addChildDuringUpdating(new Food(getRealCollisionRect().x, getRealCollisionRect().y));
							}
							for (int i = 0; i < 5; ++i)
							{
								getParent()->addChildDuringUpdating(new Jewel(getRealCollisionRect().x, getRealCollisionRect().y));
							}
							getParent()->addChildRemoving(this);
							break;
						default:
							break;
					}
				});

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

void EnemyHuman1::collision(DisplayObject* obj)
{
	if (obj->getType() == GameObjectType::PLAYER_ATTACK && !isHit())
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		//dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
		//std::cout << " aaa" << std::endl;
	}
}

void EnemyHuman1::hit()
{
	if (!isHit())
	{
		SoundManager::Instance().playSound(SoundID::HIT);
		getParent()->addChildDuringUpdating(new Particle(getRealCollisionRect().x, getRealCollisionRect().y, getRealCollisionRect().w, getRealCollisionRect().h, ParticleType::HIT));
	}
	Character::hit();
}

void EnemyHuman1::die()
{

	Character::die();
}
