#include "Listener.h"
#include "EffectManager.h"
#include "ActorHealEvent.h"
#include <iostream>
#include "CollisionListener.h"
#include "Player.h"
#include "HealthPackActor.h"
#include <chrono>
#include <iostream>
#include "FearActor.h"
#include "CoinActor.h"

using namespace std;
using namespace chrono;

class ItemCollisionListener : public CollisionListener {

public:


	virtual void onInput(CollisionEvent * e) {
		
		if (auto act = std::dynamic_pointer_cast<Player>(e->getActorA())) { // Check if the collision is with a player
			if (auto heal = std::dynamic_pointer_cast<HealthPackActor>(e->getActorB())) { // If its a health pack
				if (act->getHealth() == act->getMaxHealth()) {
					act->setMaxHealth(act->getMaxHealth() + 50); // Increase max health by 50
				}

				// Effect lasts for 5 seconds.
				EffectManager::addEffect(*act, heal->getEffect(), 5000);
				SceneManager::getInstance()->getPendingRemoval().push_front(heal);
			}else if(auto fear = std::dynamic_pointer_cast<FearActor>(e->getActorB())){ // if its a fear item
				// Fear effect lasts for 10 seconds
				EffectManager::addEffect(*act, fear->getEffect(), 10000); // Adds fear effect for 10 seconds
				SceneManager::getInstance()->getPendingRemoval().push_front(fear);
			}
			else if (auto coin = std::dynamic_pointer_cast<CoinActor>(e->getActorB())) { // if its a coin
				SceneManager::getInstance()->setScore(SceneManager::getInstance()->getScore() + 1); // Increments score by 1
				SceneManager::getInstance()->getPendingRemoval().push_front(coin);
			}else if(auto enemy = std::dynamic_pointer_cast<Enemy>(e->getActorB())){ // if its an enemy,
				enemy->setState(EnemyState::EXPLODE); // Blow up
			}
		}
		

		
	}

};