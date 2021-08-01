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

private:

	std::vector<SDL_Rect> m_foodTexturePosition;
	SDL_Rect m_currentPosition;

	float m_time;


};

#endif // __FOOD__