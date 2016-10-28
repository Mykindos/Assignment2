#include "EffectActor.h"
class HealthPackActor : public EffectActor {

public:
	HealthPackActor() : EffectActor(EffectType::SLOWHEAL, "textures//full.bmp", POINT2(rand() % 1000, rand() % 1000)) {

	}

	virtual ActorType getType() {
		return ActorType::EFFECT;
	}

	virtual void update() {

	}

};