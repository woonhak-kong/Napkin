#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"
class Background : public DisplayObject
{
public:
	Background();
	~Background() = default;
	void draw() override;
	void update() override;
	void clean() override;

private:

	// temporary

};

#endif // __BACKGROUND__