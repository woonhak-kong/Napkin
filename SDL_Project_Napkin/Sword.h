#pragma once
#ifndef __SWORD__
#define __SWORD__
#include "PhysicsObject.h"
#include "SwordType.h"

class Sword : public PhysicsObject
{
public:
	Sword(int power, int reach, int maxDurability, SwordType type);
	virtual ~Sword() = default;
	virtual void draw();
	virtual void update();
	virtual void clean();
	void collision(DisplayObject* obj) override;

	int getPower() const;
	int getReach() const;
	int getDurability() const;
	SwordType getSwordType() const;

	void setDurability(int value);


private:

	int m_attackPower;
	int m_reach;
	int m_durability;
	int m_maxDurability;

	SwordType m_swordType;

};
#endif // __SWORD__