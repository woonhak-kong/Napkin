#pragma once
#ifndef __KNIGHT_AI__
#define __KNIGHT_AI__

#include "GameAI.h"
//#include "Character.h"

class Character;
class KnightAI : public GameAI
{
public:
	KnightAI(Character* character);
	~KnightAI() = default;
	void update() override;

private:

};

#endif //__KNIGHT_AI__