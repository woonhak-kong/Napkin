#pragma once
#ifndef __ENEMY_HUMAN1__
#define __ENEMY_HUMAN1__
#include "Character.h"
class EnemyHuman1 : public Character
{
public:
	EnemyHuman1(const LoaderParams& loader);
	virtual ~EnemyHuman1();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif // __ENEMY_HUMAN1__
