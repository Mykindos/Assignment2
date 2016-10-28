#pragma once
#include "Event.h"
#include "Actor.h"
#include <memory>
#include <iostream>

class ActorHealEvent : public Event {

public:
	ActorHealEvent(std::shared_ptr<Actor> actor);

	std::shared_ptr<Actor> getActor() {
		return m_actor;
	}
private:
	std::shared_ptr<Actor> m_actor;
};