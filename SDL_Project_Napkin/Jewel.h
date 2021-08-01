#pragma once
#ifndef __JEWEL__
#define __JEWEL__


#include "PhysicsObject.h"



class Jewel : public PhysicsObject
{
public:
	Jewel(int x, int y);
	~Jewel() override;
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void collision(DisplayObject* obj) override;

private:
	std::vector<SDL_Rect> m_JewelPosition;
	SDL_Rect m_currentPosition;


};

#endif // !__JEWEL__
