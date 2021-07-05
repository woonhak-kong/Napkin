#pragma once
#include "Sprite.h"
class AttackBox : public Sprite
{
public:
	AttackBox(SDL_Rect rect, glm::vec2 velocity, int distance, GameObjectType attackType, int power);
	virtual ~AttackBox();
	void draw() override;
	void update() override;
	void clean() override;
	int getAttackPower() const;
	void deleteAttackBox();

private:

	int m_power;
	int m_distance4Delete;
	int m_startingPoint;
	bool m_isDeleted;

};

