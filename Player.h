#pragma once
#include "CircleActor.h"
#include <iostream>
#include <string>
#include "Command.h"
#include "PlayerShootBulletCommand.h"
class Player : public CircleActor {

public:
	Player(double radius, long fillColour, long outerColour, POINT2 pos, double speed);
	//PlayerTank();
	Player(double speed);
	~Player() {};
	virtual ActorType getType();
	virtual void update();


	double getSpeed();
	int getHealth();
	int getMaxHealth();
	void setHealth(int);
	void setMaxHealth(int);


private:
	int m_health = 100;
	int m_maxHealth = 100;
	double m_speed;
};