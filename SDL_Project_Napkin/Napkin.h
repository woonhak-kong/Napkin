#pragma once
#include "Character.h"
class Napkin : public Character
{
public:
	Napkin(const LoaderParams& loader);
	~Napkin();

	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;

	void handleEvent();


};

