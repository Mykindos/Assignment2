#pragma once
#include "ActorType.h"
#include <iostream>
#include <list>
#include "Actor.h"
#include <memory>
#include "Player.h"

class ActorFactory {

	static ActorFactory * instance;


public:

	/*
	Singleton getter
	*/
	static ActorFactory *getInstance() {
		if (!instance) {
			instance = new ActorFactory();
		}
		return instance;
	}

	/*
		Actor management
	*/
	std::shared_ptr<Actor> createActor(ActorType type);
	std::shared_ptr<Actor> createEffectActor(EffectType effect);

	/*
		File Management
	*/
	void loadProperties();
	double getPlayerSpeed();

private:

	double bulletSpeed = 0.5;
	double playerSpeed = 0.5;
	double enemySpeed = 0.5;
};