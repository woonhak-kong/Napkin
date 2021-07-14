#pragma once
#include "Character.h"
#include "EnergyBar.h"
#include "Sword.h"

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

	void changeSwordRight();
	void changeSwordLeft();

	bool getGameOver() const;
	bool getGameClear() const;

private:
	EnergyBar* m_energyBar;
	bool m_gameOver;
	bool m_gameClear;
	int m_jumpNum;

	bool m_isJumpPushed;
	int m_hitMotionNum;

	std::vector<Sword*> m_swordVector;
	int m_swordIdx;
};

