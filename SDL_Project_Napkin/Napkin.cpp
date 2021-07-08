#include "Napkin.h"

#include <iostream>

#include "AttackBox.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Game.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "TextureManager.h"

Napkin::Napkin(const LoaderParams& loader) :
	Character(loader),
	m_energyBar(nullptr),
	m_gameOver(false)
{

	//todo / we should control load function XML
	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "napkin";

	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-00.png", "idle0");
	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-01.png", "idle1");
	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-02.png", "idle2");
	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-03.png", "idle3");
	size = TextureManager::Instance().getTextureSize("idle0");

	animation.name = "idle";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "idle" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-00-1.3.png", "attack1_0");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-01-1.3.png", "attack1_1");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-02-1.3.png", "attack1_2");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-03-1.3.png", "attack1_3");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-04-1.3.png", "attack1_4");

	animation.name = "attack1";
	for (int i = 0; i < 5; ++i)
	{
		frame.name = "attack1_" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-00-1.3.png", "attack2_0");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-01-1.3.png", "attack2_1");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-02-1.3.png", "attack2_2");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-03-1.3.png", "attack2_3");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-04-1.3.png", "attack2_4");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-05-1.3.png", "attack2_5");

	animation.name = "attack2";
	for (int i = 0; i < 6; ++i)
	{
		frame.name = "attack2_" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-00-1.3.png", "attack3_0");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-01-1.3.png", "attack3_1");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-02-1.3.png", "attack3_2");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-03-1.3.png", "attack3_3");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-04-1.3.png", "attack3_4");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-05-1.3.png", "attack3_5");

	animation.name = "attack3";
	for (int i = 0; i < 6; ++i)
	{
		frame.name = "attack3_" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-00.png", "run0");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-01.png", "run1");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-02.png", "run2");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-03.png", "run3");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-04.png", "run4");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-05.png", "run5");

	animation.name = "run";
	for (int i = 0; i < 6; ++i)
	{
		frame.name = "run" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-00.png", "jump0");
	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-01.png", "jump1");
	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-02.png", "jump2");
	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-03.png", "jump3");

	animation.name = "jump";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "jump" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();


	TextureManager::Instance().load("assets/characters/player/fall/adventurer-fall-00.png", "fall0");
	TextureManager::Instance().load("assets/characters/player/fall/adventurer-fall-00.png", "fall1");

	animation.name = "fall";
	for (int i = 0; i < 2; ++i)
	{
		frame.name = "fall" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	// dead
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-00.png", "die0");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-01.png", "die1");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-02.png", "die2");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-03.png", "die3");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-04.png", "die4");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-05.png", "die5");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-06.png", "die6");


	animation.name = "die";
	for (int i = 0; i < 7; ++i)
	{
		frame.name = "die" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	setAnimation(TextureManager::Instance().getAnimation("napkin"));




	// todo
	// when character is created, must to be set.
	setType(GameObjectType::PLAYER);
	setAttackType(GameObjectType::PLAYER_ATTACK);
	/////////////////////////////////////////////////

	setAttackSpeed(2);
	setAttackReach(100);
	/*std::cout << getAnimation("attack2").frames.size()<< std::endl;
	setAttackSpeed(getAnimation("attack2").frames.size()* round(getAnimation("attack2").frames.size() / 2 / 0.5f));*/

	// only player can have Camera.
	Camera::Instance().setTarget(&getTransform().getPosition());

	//UI
	m_energyBar = new EnergyBar(loader.m_maxHp);
}

Napkin::~Napkin()
{

}

void Napkin::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation("idle"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);

			break;
		case CharacterState::ATTACK:
			TextureManager::Instance().playAnimation(getAnimation("attack2"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), getAttackSpeed(), 0.0f, 255, flip, true, [&](CallbackType type) -> void
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
				},3);
			break;
		case CharacterState::RUN:
			TextureManager::Instance().playAnimation(getAnimation("run"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::JUMP:
			TextureManager::Instance().playAnimation(getAnimation("jump"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip );
			break;
		case CharacterState::FALL:
			TextureManager::Instance().playAnimation(getAnimation("fall"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation("die"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							m_gameOver = true;
							break;
						default:
							break;
					}
				});
			break;
	}

	//UI
	m_energyBar->draw();
}

void Napkin::update()
{
	handleEvent();
	Character::update();

}

void Napkin::clean()
{
	delete m_energyBar;
}

void Napkin::hit()
{
	m_energyBar->setEnergy(getPresentHp());
}

void Napkin::collision(DisplayObject* obj)
{
	if (obj->getType() == GameObjectType::ENEMY_ATTACK)
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
	}
}

void Napkin::die()
{
	setIsDead(true);
	setCurrentState(CharacterState::DEAD);
}

void Napkin::handleEvent()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		moveToRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LEFT))
	{
		moveToLeft();
	}
	else
	{
		idle();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		jump();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_F))
	{
		if (!isDead() && !isAttacking())
		{
			SoundManager::Instance().playSound(SoundID::ATTACK);
		}
		attack();
	}
}

bool Napkin::getGameOver() const
{
	return m_gameOver;
}
