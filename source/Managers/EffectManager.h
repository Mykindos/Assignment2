#include "Actor.h"
#include <chrono>
#include <iostream>
#include "SceneManager.h"

using namespace std;
using namespace chrono;

class EffectManager {

public:
	static void addEffect(Actor & actor, EffectType effect, long long duration) {
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		actor.getEffects().push_front(Effect(effect, ms.count() + duration));

	}

	// Removes all effects from an actor matching the specified type
	static void removeEffect(Actor & actor, EffectType effect) {
		std::list<Effect> remove;
		for (Effect e : actor.getEffects()) {
			if (e.getType() == effect) {
				remove.push_back(e);
			}
		}

		for (Effect e : remove) {
			actor.getEffects().remove(e);
		}
	}

	/*
		Loops through all actors and there effects,
		checks if there is any time remaining on the effect
		if there isnt, removes the effect.
	*/
	static void processEffects() {
		list<Effect> remove;
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		for (auto act : SceneManager::getInstance()->getActors()) {
			for (Effect e : act->getEffects()) {
				if (e.getDuration() - ms.count() <= 0) {
					remove.push_front(e);
				}
			}
			for (Effect e : remove) {
				act->getEffects().remove(e);
			}
			remove.clear();
		}

		
	}


	/*
		Returns true if the actors effect list contains the specified effect
	*/
	static bool hasEffect(Actor & act, EffectType effect) {
		for (Effect e : act.getEffects()) {
			if (e.getType() == effect) {
				return true;
			}
		}
		return false;
	}

};