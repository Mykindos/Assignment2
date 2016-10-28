#pragma once
#include "EffectActor.h"
class FearActor : public EffectActor {

public:
	FearActor() : EffectActor(EffectType::FEAR, "textures//goldskull.bmp", POINT2(rand() % 1000, rand() % 1000)) {

	}

	virtual ActorType getType() {
		return ActorType::EFFECT;
	}

	virtual void update() {

	}

};