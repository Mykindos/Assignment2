#pragma once
#include "CollisionEvent.h"
#include "Listener.h"
#include <iostream>
#include <string>
class CollisionListener : public Listener {
public:
	virtual void onInput(CollisionEvent * e) {};

	virtual std::string getType() {
		return "CollisionListener";
	}
};