#pragma once
#ifndef __BASIC_SWORD__
#define __BASIC_SWORD__
#include "Sword.h"
class BasicSword final : public Sword
{
public:
	BasicSword(int power, int reach, int maxDurability);
	~BasicSword();
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
};

#endif // __BASIC_SWORD__