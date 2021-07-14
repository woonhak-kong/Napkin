#pragma once
#ifndef __FIRE_SWORD__
#define __FIRE_SWORD__
#include "Sword.h"
class FireSword final : public Sword
{
public:
	FireSword(int power, int reach, int maxDurability);
	~FireSword();
	void draw() override;
	void update() override;
	void clean() override;
	void collision(::DisplayObject* obj) override;
};

#endif // __FIRE_SWORD__