#pragma once
#include "CircleActor.h"
#include "EnemyState.h"

class Enemy : public CircleActor {

public:
	Enemy(double radius, long fillColour, long outerColour, POINT2 pos);
	~Enemy() {};
	virtual ActorType getType();
	virtual void update();

	int getRandom();
	EnemyState getState() {
		return m_state;
	}

	void repurpose();

	/*
		State methods
	*/
	void flee();
	void heal();
	void patrol();
	void pursue();
	void explode();
	void setState(EnemyState state);
	
private:

	EnemyState m_state = EnemyState::PATROL;
	long long updateTimer = 0;
	POINT2 m_target = POINT2(500, 500);
};