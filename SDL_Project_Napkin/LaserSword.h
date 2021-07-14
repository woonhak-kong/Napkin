#pragma once
#ifndef __LASER_SWORD__
#define __LASER_SWORD__
#include "Sword.h"
class LaserSword final : public Sword
{
public:
	LaserSword(int power, int reach, int maxDurability);
	~LaserSword();
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
};

#endif // __LASER_SWORD__