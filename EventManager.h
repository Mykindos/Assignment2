#pragma once
#include <iostream>
#include <list>
#include "Listener.h"
#include "Event.h"
class EventManager {

	static EventManager * instance;


public:

	/*
		Singleton getter
	*/
	static EventManager *getInstance() {
		if (!instance) {
			instance = new EventManager();
		}
		return instance;
	}

	void callEvent(Event * e);

	/*
	  Register a listener by adding it to the list
	*/
	void addListener(Listener * n) {
		listeners.push_back(n);
	}
	
	/*
		Returns list of listeners
	*/
	std::list<Listener*> getListeners() {
		return listeners;
	}

private:
	//EventManager(); // Enforce singleston
	std::list<Listener*> listeners;

};