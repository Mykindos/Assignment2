#include "EventManager.h"
#include "Event.h"
#include "InputListener.h"
#include <iostream>
#include "CollisionListener.h"
#include "ActorHealEvent.h"

EventManager* EventManager::instance;

/*
	Calls the event specified by passing it on to listeners that support the event type
	Downcasts to match event to appropriate listener.
*/
void EventManager::callEvent(Event * e) {
	for (Listener * l : listeners) {

		// If its an InputListener
		if (auto temp = dynamic_cast<InputListener*>(l)) {

			auto ie = dynamic_cast<InputEvent*>(e);
			if (ie) {
				temp->onInput(ie); // Call the onInput method for each one
			}


		} else if(auto temp = dynamic_cast<CollisionListener*>(l)){
			if (auto ce = dynamic_cast<CollisionEvent*>(e)) {
				temp->onInput(ce);
			}
		}
	}
}

