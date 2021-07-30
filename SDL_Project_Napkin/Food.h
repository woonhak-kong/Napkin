#pragma once
#ifndef __FOOD__
#define __FOOD__
#include "PhysicsObject.h"
class Food : public PhysicsObject
{
public:
	Food(int x, int y);
	~Food() override;
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
};

#endif // __FOOD__