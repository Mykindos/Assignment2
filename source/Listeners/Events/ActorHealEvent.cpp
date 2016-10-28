#include "ActorHealEvent.h"

ActorHealEvent::ActorHealEvent(std::shared_ptr<Actor> actor) {
	m_actor = actor;
}