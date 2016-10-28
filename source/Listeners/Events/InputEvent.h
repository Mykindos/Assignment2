#pragma once
#include "Event.h"
#include <iostream>
#include <string>
#include <memory>
#include "Player.h"


class InputEvent : public Event {


public:
	InputEvent(char key, std::shared_ptr<Player> actor);

	char getKey() {
		return m_key;
	}

	std::shared_ptr<Player> getActor() {
		return m_actor;
	}

	virtual std::string getType() {
		return "InputEvent";
	}

private:
	char m_key;
	std::shared_ptr<Player> m_actor;
};