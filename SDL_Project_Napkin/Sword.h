#pragma once
#include "PhysicsObject.h"
class Sword : public PhysicsObject
{
public:
	Sword(int power, int reach, int maxDurability);
	virtual ~Sword() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	void collision(DisplayObject* obj) override;


private:

	int m_attackPower;
	int m_reach;
	int m_durability;
	int m_maxDurability;

};

