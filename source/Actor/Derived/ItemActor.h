#pragma once
#include "TexturedActor.h"
#include <iostream>
#include <string>
class ItemActor : public TexturedActor {

public:
	ItemActor(std::string file, POINT2 pos);

	virtual ActorType getType() = 0;
	virtual void update() = 0;

};