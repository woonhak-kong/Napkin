#ifndef __LAYER__
#define __LAYER__

class Layer
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual ~Layer() = default;
};


#endif // !__LAYER__

