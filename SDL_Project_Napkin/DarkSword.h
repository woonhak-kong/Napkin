#pragma once
#ifndef __DARK__SWORD__
#define __DARK__SWORD__
#include "Sword.h"
class DarkSword final : public Sword
{
public:
	DarkSword(int power, int reach, int maxDurability);
	~DarkSword();
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
};

#endif // __DARK__SWORD__