#include "CollisionEvent.h"


// Creates a collision event between 2 actors
CollisionEvent::CollisionEvent(std::shared_ptr<Actor> a, std::shared_ptr<Actor> b) {
	m_aActor = a;
	m_bActor = b;
}