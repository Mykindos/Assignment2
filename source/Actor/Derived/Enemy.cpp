#include "Enemy.h"
#include <iostream>
#include <string>
#include <chrono>
#include "SceneManager.h"
#include "Steering.h"
#include "EffectManager.h"
#include <random>

using namespace std;
using namespace chrono;


Enemy::Enemy(double radius, long fillColour, long outerColour, POINT2 pos) : CircleActor(radius, fillColour, outerColour, pos) {

}


// Generates random number between 1 and 1000
// Taken from http://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
// As rand() wasn't random enough for my liking
int Enemy::getRandom() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1, 1000);

	return dist(mt);
}


void Enemy::update() {

	switch (getState()) {
	case PURSUIT:
		// If a player is spotted, the enemy will chase the player until they are out of range, or dead.
		pursue();
		break;
	case EXPLODE:
		// Death state
		explode();
		break;
	case PATROL:
		// Standard movement around the game, stops players from safespotting
		patrol();
		break;
	case FLEE:
		// If the player has an effect called Fear, enemies will flee the player for the duration of the effect
		flee();
		break;
	}
	
}

void Enemy::pursue() {
	for (shared_ptr<Actor> act : SceneManager::getInstance()->getActors()) {
		if (shared_ptr<CircleActor> ca = dynamic_pointer_cast<CircleActor>(act)) {


			// If its an enemy, check for collision if they are in pursue mode.
			if (shared_ptr<Enemy> ea = dynamic_pointer_cast<Enemy>(ca)) {
				if (ea->getPosition() != getPosition()) {
					if (SceneManager::getInstance()->distance(*this, *ea) <= ea->getRadius() + getRadius()) {
						setState(EnemyState::EXPLODE);
						
					}
				}

			}else if (shared_ptr<Player> pa = dynamic_pointer_cast<Player>(ca)) { // If its a player

				if (SceneManager::getInstance()->distance(*this, *pa) < 150) { // Check if they are within 150 
					VECTOR2 force = Steering::seek(*this, SceneManager::getInstance()->getPlayer()->getPosition()); // Gets force towards player
					m_velocity = m_velocity + force / 50;
					m_pos = m_pos + m_velocity * 0.025; // Update position with latest velocity
				}
				else {
					setState(EnemyState::PATROL);
				}

			}
		}
	}
}

void Enemy::flee() {
	if (SceneManager::getInstance()->distance(*this, *SceneManager::getInstance()->getPlayer()) < 150) { // Check if they are within 150 
		VECTOR2 force = Steering::flee(*this, SceneManager::getInstance()->getPlayer()->getPosition()); // Gets force towards player
		m_velocity = m_velocity + force / 50;
		m_pos = m_pos + m_velocity * 0.015; // Update position with latest velocity
	}
	else {
		setState(EnemyState::PATROL);
	}
}

void Enemy::heal() {

}

void Enemy::patrol() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if (updateTimer - ms.count() <= 0) {
		m_target = POINT2(getRandom(), getRandom());
		updateTimer = ms.count() + 2000;
	}
	bool skip = false;
	for (auto i : SceneManager::getInstance()->getActors()) {
		if (shared_ptr<Enemy> ea = dynamic_pointer_cast<Enemy>(i)) {
			if (getPosition() != ea->getPosition()) {
				if (SceneManager::getInstance()->distance(*this, *ea) < 150) {
					m_target = POINT2(getRandom(), getRandom());
					VECTOR2 fleeForce = Steering::flee(*this, ea->getPosition());
					m_velocity = m_velocity + fleeForce / 50;
					m_pos = m_pos + m_velocity * 0.025;
					skip = true;
				}
			}
		}else if(shared_ptr<Player> ea = dynamic_pointer_cast<Player>(i)) {
			if (getPosition() != ea->getPosition()) {
				if (SceneManager::getInstance()->distance(*this, *ea) < 150) {
					if (EffectManager::hasEffect(*ea, EffectType::FEAR)) {
						setState(EnemyState::FLEE);
					}else{
						setState(EnemyState::PURSUIT);
					}
					return;
				}
			}
		}
	}

	if (!skip) {
		VECTOR2 force = Steering::seek(*this, m_target); // Gets force towards player
		m_velocity = m_velocity + force / 50;
		m_pos = m_pos + m_velocity * 0.015; // Update position with latest velocity
	}

	
	


}

void Enemy::explode() {
	for (shared_ptr<Actor> act : SceneManager::getInstance()->getActors()) {
		if (SceneManager::getInstance()->distance(*act, *this) <= 100) {
			if (shared_ptr<CircleActor> ca = dynamic_pointer_cast<CircleActor>(act)) {
				if (shared_ptr<Player> pa = dynamic_pointer_cast<Player>(ca)) { // If its a player
					pa->setHealth(pa->getHealth() - 50);
					if (pa->getHealth() <= 0) {
						exit(0); // Game ends
					}
				}
				else {
					if (shared_ptr<Enemy> ea = dynamic_pointer_cast<Enemy>(act)) {
						if (ea->getPosition() != getPosition()) {
							//ea->explode(); // Chain explosions :)
						}
						SceneManager::getInstance()->getEnemyPool().push_front(ea);
						SceneManager::getInstance()->getPendingRemoval().push_front(act);
					}
				}
			}
		}
	}


}

void Enemy::repurpose() {
	setState(EnemyState::PURSUIT);
	setPosition(POINT2(rand() % 1000 + 1, rand() % 1000 + 1));

}

void Enemy::setState(EnemyState state) {
	m_state = state;
}



ActorType Enemy::getType() {
	return ActorType::ENEMY;
}