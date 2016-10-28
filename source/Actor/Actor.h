#pragma once
#include "math\Geometry.h"
#include "ActorType.h"
#include "Effect.h"
#include <list>

class Actor {

public:
	Actor() {};
	Actor(POINT2 pos);
	~Actor() {};
	POINT2 getPosition();
	virtual ActorType getType() = 0;
	virtual void update() = 0;
	void setPosition(POINT2 pos);
	VECTOR2 getVelocity();
	std::list<Effect> & getEffects();
	void setVelocity(VECTOR2 velocity);
	bool isOffScreen();
protected:
	POINT2 m_pos;
	VECTOR2 m_velocity = VECTOR2(0, 0);
	std::list<Effect> m_effects;

};