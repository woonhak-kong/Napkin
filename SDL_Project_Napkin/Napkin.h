#pragma once
#include "Character.h"
#include "EnergyBar.h"
#include "Label.h"
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

	void cleanSword();

	void reloadTexture();

private:
	EnergyBar* m_energyBar;
	Label* m_swordDurability;

	bool m_gameOver;
	int m_jumpNum;

	bool m_isJumpPushed;
	bool m_isQEPushed;
	bool m_isHPushed;
	int m_hitMotionNum;

	std::vector<Sword*> m_swordVector;
	int m_swordIdx;

private:

	void m_setSwordUI();
	void m_removeZeroDurabilitySword();
	void m_setSwordProperty();
};

