#pragma once
#include "PhysicsObject.h"
class Sword : public PhysicsObject
{
public:
	Sword(int power, int reach, int maxDurability);
	virtual ~Sword() = default;
	virtual void draw();
	virtual void update();
	virtual void clean();
	void collision(DisplayObject* obj) override;


private:

	int m_attackPower;
	int m_reach;
	int m_durability;
	int m_maxDurability;

};

