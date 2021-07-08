#pragma once
#include "Character.h"
#include "EnergyBar.h"

class Napkin : public Character
{
public:
	Napkin(const LoaderParams& loader);
	~Napkin();

	void draw() override;
	void update() override;
	void clean() override;

	void hit() override;
	void collision(DisplayObject* obj) override;

	void die() override;
	void handleEvent();

	bool getGameOver() const;

private:
	EnergyBar* m_energyBar;
	bool m_gameOver;
	int m_jumpNum;

	bool m_isJumpPushed;
};

