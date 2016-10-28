#pragma once
#include "InputEvent.h"
#include "Listener.h"
#include <iostream>
#include <string>
class InputListener : public Listener{
public:
	virtual void onInput(InputEvent * e) {};

	virtual std::string getType() {
		return "InputListener";
	}
};