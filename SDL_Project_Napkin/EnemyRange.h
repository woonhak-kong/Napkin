#pragma once
#include "Character.h"

class EnemyRange : public Character
{
public:
	EnemyRange(const LoaderParams& loader);
	virtual ~EnemyRange();

	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;

	void hit() override;
	void die() override;

};

