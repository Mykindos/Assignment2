#pragma once
#include "Event.h"
#include <iostream>
#include <string>
#include <memory>
#include "Actor.h"

class CollisionEvent : public Event {


public:
	CollisionEvent( std::shared_ptr<Actor> a, std::shared_ptr<Actor> b);

	char getKey() {
		return m_key;
	}

	std::shared_ptr<Actor> getActorA() {
		return m_aActor;
	}

	std::shared_ptr<Actor> getActorB() {
		return m_bActor;
	}

	virtual std::string getType() {
		return "CollisionEvent";
	}

private:
	char m_key;
	std::shared_ptr<Actor> m_aActor;
	std::shared_ptr<Actor> m_bActor;
};