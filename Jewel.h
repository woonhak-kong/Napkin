#pragma once
#include "Character.h"


class Jewel : public Character
{
	Jewel(const LoaderParams& loader);
	~Jewel();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
    void handleEvent();

};