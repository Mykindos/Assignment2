
#include "InputEvent.h"
#include "math/Geometry.h"
#include "Player.h"
#include <iostream>
#include <memory>
/*
	Define an InputEvent by specifying the key pressed, and an actor you want to affect
*/
InputEvent::InputEvent(char key, std::shared_ptr<Player> actor) {
	m_key = key;
	m_actor = actor;
}