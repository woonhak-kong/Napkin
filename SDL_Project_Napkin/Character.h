#pragma once
#include "CharacterState.h"
#include "GameAI.h"
#include "Layer.h"
#include "LoaderParams.h"
#include "PhysicsObject.h"
class Character : public PhysicsObject
{
public:
	Character(const LoaderParams& loader);
	virtual ~Character() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();

	void collision(DisplayObject* obj) override;
	// getter
	float getMoveSpeed() const;
	float getAttackSpeed() const;
	CharacterState getCurrentState() const;
	bool isFlip() const;
	bool isAttacking() const;
	bool isHit() const;
	SDL_Rect getAttackCollisionRect() const;
	GameAI* getGameAI() const;
	int getPresentHp() const;
	// setter
	void setMoveSpeed(float speed);
	void setAttackSpeed(float speed);
	void setCurrentState(CharacterState state);
	void setAttackReach(int reach);
	void setAttackType(GameObjectType attackType);
	void setIsAttacking(bool attacking);
	void setIsHit(bool hit);
	void setGameAI(GameAI* ai);

	void takeDamage(int damage);

	void jump();
	void moveToRight();
	void moveToLeft();
	void idle();
	void attack();
	virtual void hit();
	virtual void die();
	void makingAttackCollisionBox();





private:
	bool m_isJumping;
	bool m_isAttacking;
	bool m_isHit;
	bool m_isFlip;

	SDL_Rect m_attackCollisionRect;

	float m_moveSpeed;
	float m_attackSpeed;
	int m_attackReach;

	CharacterState m_curState;
	GameObjectType m_attackType;

	int m_presentHp;
	int m_maxHp;
	int m_attackPower;

	GameAI* m_ai;



private:



	void m_setAttackRectSize(int w, int h);
};


