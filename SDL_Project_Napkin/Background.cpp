#include "Background.h"

#include "Config.h"
#include "TextureManager.h"

Background::Background()
{
	TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/background1.png", "background1");
	TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/background2.png", "background2");
	TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/background3.png", "background3");
	TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/background4.png", "background4");
	TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/background5.png", "background5");
	TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/background6.png", "background6");
	//setType(GameObjectType::NONE);
}

void Background::draw()
{
	TextureManager::Instance().draw("background1", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background2", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background3", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background4", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background5", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background6", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
}

void Background::update()
{
}

void Background::clean()
{
}
