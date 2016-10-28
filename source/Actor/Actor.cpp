#include "Actor.h"


Actor::Actor(POINT2 pos)
{
	m_pos = pos;
}


bool Actor::isOffScreen() {
	return getPosition().y < -50 || getPosition().y > 1050;
}

POINT2 Actor::getPosition()
{
	return m_pos;
}

std::list<Effect> & Actor::getEffects() {
	return m_effects;
}

VECTOR2 Actor::getVelocity() {
	return m_velocity;
}

void Actor::setVelocity(VECTOR2 velocity) {
	m_velocity = velocity;
}

void Actor::setPosition(POINT2 pos)
{
	m_pos = pos;
}
