#pragma once
#ifndef __PARTICLE__
#define __PARTICLE__
#include "ParticleType.h"
#include "Sprite.h"
class Particle : public Sprite
{
public:
	Particle(int x, int y, int width, int height, ParticleType type);
	~Particle();
	void draw() override;
	void update() override;
	void clean() override;

private:
	ParticleType m_type;

};

#endif // __PARTICLE__