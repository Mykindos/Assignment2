#pragma once
#include "TexturedActor.h"
#include <iostream>
#include <string>

class EffectActor : public TexturedActor {

public:
	EffectActor(EffectType effect, std::string file, POINT2 pos);

	virtual ActorType getType() = 0;
	virtual void update() = 0;
	EffectType getEffect() {
		return m_effect;
	}
private:
	EffectType m_effect;
};
