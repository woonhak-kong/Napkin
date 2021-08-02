#include "EnemyRange.h"

#include "AttackBox.h"
#include "CallbackType.h"
#include "Camera.h"
#include "EnemyRangeAI.h"
#include "Explosion.h"
#include "Food.h"
#include "Jewel.h"
#include "MagicBall.h"
#include "Particle.h"
#include "ParticleType.h"
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
	setGameAI(new EnemyRangeAI(this));
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
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255, flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
						{
							SDL_Rect tmpR{ 0,0,42,60 };

							if (isFlip())
							{
								// Left Direction
								tmpR.x = getRealCollisionRect().x - tmpR.w;
								tmpR.y = getRealCollisionRect().y;

							}
							else
							{
								// Right Direction
								tmpR.x = getRealCollisionRect().x + getRealCollisionRect().w;
								tmpR.y = getRealCollisionRect().y;
							}
							getParent()->addChildDuringUpdating(new AttackBox(tmpR, glm::vec2(0, 0),
								0, GameObjectType::NONE, 0, isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, SwordType::SHOT));

							getParent()->addChildDuringUpdating(new MagicBall({ tmpR.x + 15, tmpR.y + 20 }, { isFlip() ? -150 : 150,-100 },
								GameObjectType::ENEMY_ATTACK, 10, MagicBallType::BALL1, getParent()->getPlayer()));
							SoundManager::Instance().playSound(SoundID::SHOT);
						}
							break;
						case CallbackType::ANIMATION_END:
							this->setIsAttacking(false);
							break;
						default:
							break;
					}

				}, 1);
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
							//std::cout << "die call back" << std::endl;
							ScoreManager::addScore(10);
							getParent()->addChildDuringUpdating(new Explosion(getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getWidth(), ExplosionType::EXPLOSION_BIG));
							if (getParent()->getState() == SceneState::TUTORIAL_SCENE)
							{
								getParent()->addChildDuringUpdating(new Sword(getRealCollisionRect().x, getRealCollisionRect().y, static_cast<SwordType>(rand() % 3 + 1)));
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
		getParent()->addChildDuringUpdating(new Particle(getRealCollisionRect().x, getRealCollisionRect().y, getRealCollisionRect().w, getRealCollisionRect().h, ParticleType::HIT));
		SoundManager::Instance().playSound(SoundID::HIT);
	}
	Character::hit();
}

void EnemyRange::die()
{
	Character::die();
}
