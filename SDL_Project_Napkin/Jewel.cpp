#include "Jewel.h"
#include "Camera.h"
#include "EventManager.h"
#include "TextureManager.h"

Jewel::Jewel(const LoaderParams& loader) :
	Character(loader)
{
	
}


Jewel::~Jewel()
{

}

void Jewel::draw()
{
	Character::draw;
}

void Jewel::update()
{
	handleEvent();
	Character::update();
}

void Jewel::clean()
{

}


void Jewel::handleEvent()
{

}



