#include "SceneManager.h"
#include "ui/InputState.h"
#include "EventManager.h"
#include "InputEvent.h"
#include "ActorFactory.h"
#include "Player.h"
#include <iostream>
#include <list>
#include <string>
#include <cmath>
#include "CollisionListener.h"
#include "TexturedActor.h"
#include "EffectManager.h"




SceneManager* SceneManager::instance;
using namespace std;
using namespace std::chrono;

void SceneManager::addEnemies() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());


	// Check if it has been 2 seconds since the last enemy
	if (lastEnemy - ms.count() <= 0) {
		

		// If our enemy pool doesnt contain 5 enemies, create a tank normally
		if (getEnemyPool().size() < 5) {
			int count = 0;
			for (auto i : getActors()) {
				if (shared_ptr<Enemy>  et = dynamic_pointer_cast<Enemy>(i)) {
					count++;
				}
			}
			if (count < 4) { // Max of 7 enemies at all times
				addActor(ActorType::ENEMY);
			}
		} else {
			// If it does contain 5, then there is no need to create more, we can simply reuse our old ones.
			shared_ptr<Enemy> & enemy = getEnemyPool().front(); // Grab the first pooled enemy in the list
			enemy->repurpose();
			getActors().push_back(enemy);
			getEnemyPool().remove(enemy); // then remove it from the pool list (it will get added back later)
		}

		// 2 second gap between 
		lastEnemy = ms.count() + 2000;
	}
}

void SceneManager::addItems() {
	if (getActors().size() < 10) {
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		if (lastItem - ms.count() <= 0) {
			int rando = rand() % 10;
			if (rando == 9) {
				addEffectActor(EffectType::FEAR);
			}
			else if (rando == 8) {
				addEffectActor(EffectType::SLOWHEAL);
			}
			else {
				addActor(ActorType::SCORE);
			}
			lastItem = ms.count() + 5000;
		}
	}
}

void SceneManager::healPlayer() {
	if (EffectManager::hasEffect(*getPlayer(), EffectType::SLOWHEAL)) {
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		if (lastHeal - ms.count() <= 0) {
			getPlayer()->setHealth(getPlayer()->getHealth() + 25);
			lastHeal = ms.count() + 1000;
		}
	}
}

// Return reference to list rather than a copy
std::list<std::shared_ptr<Actor>> & SceneManager::getActors() {
	return actors;
}

std::list<std::shared_ptr<Actor>> & SceneManager::getPendingRemoval() {
	return pendingRemoval;
}

void SceneManager::addActor(ActorType t) {
	getActors().push_front(ActorFactory::getInstance()->createActor(t));
}

void SceneManager::addEffectActor(EffectType effect) {
	getActors().push_front(ActorFactory::getInstance()->createEffectActor(effect));
}

void SceneManager::createPlayer(std::shared_ptr<Player> t) {

	getActors().push_back(t);
}

void SceneManager::removeActor(std::shared_ptr<Actor> act) {
	getActors().remove(act);

}

/*
	To avoid any concurrent issues, I created a new List of Actors, and added all the actors to be removed to it.
	After the initial loop, it will loop through the other list and remove each value in it from the Scene Actors
*/
void SceneManager::processCollisions() {
	list<shared_ptr<Actor>> toRemove;	for (auto temp : getActors()) {
		if (getPlayer()->getPosition() != temp->getPosition()) {
			if (auto texture = dynamic_pointer_cast<TexturedActor>(temp)) {
				if (distance(*getPlayer(), *texture) <= (texture->getTexture()->Width() / 2) + getPlayer()->getRadius()) {
					EventManager::getInstance()->callEvent(new CollisionEvent(getPlayer(), temp));
				}
			}else if (auto enemy = dynamic_pointer_cast<Enemy>(temp)) {
				if (distance(*getPlayer(), *enemy) <= getPlayer()->getRadius() + enemy->getRadius()) {
					EventManager::getInstance()->callEvent(new CollisionEvent(getPlayer(), temp));
				}
				
			}

		}
	}

	// Easy way to prevent Concurrent Modification
	for (auto i : toRemove) {
		removeActor(i);
	}
}

std::shared_ptr<Player> SceneManager::getPlayer() {
	for (std::shared_ptr<Actor> act : getActors()) {
		auto player = std::dynamic_pointer_cast<Player>(act);
		if (player) {
			return player;
		}
	}
}


/*
	Calculates the distance between 2 actors
*/
double SceneManager::distance(Actor & a, Actor & b) {
	double x1 = a.getPosition().x;
	double x2 = b.getPosition().x;
	double y1 = a.getPosition().y;
	double y2 = b.getPosition().y;

	double xDistance = pow(x2 - x1, 2);
	double yDistance = pow(y2 - y1, 2);

	return sqrt(xDistance + yDistance);
}


void SceneManager::processInput(char c) {
	// Calls the InputEvent for the key pressed (if it matches a key specified in the char array)
	EventManager::getInstance()->callEvent(new InputEvent(c, player));
}

void SceneManager::loadScene() {
	// Creates the player
	player = std::make_shared<Player>(30, LRGB(0,255,0), LRGB(0,200,0), POINT2(500, 900), ActorFactory::getInstance()->getPlayerSpeed());
	createPlayer(player);
}


// Iterate through all of our actors, removing them if they are off the screen, and update them if they are visible.
void SceneManager::updateActors(WinCanvas & wc) {
	try {
		for (auto i : pendingRemoval) {
			removeActor(i);
		}
		pendingRemoval.clear();
		// Need a reference, not a copy of the actors
		list<shared_ptr<Actor>> & temp = getActors();		for (list<shared_ptr<Actor>>::iterator it = temp.begin(); it != temp.end(); it++) {
			shared_ptr<Actor> act = *it;
				// If the Actor is on the screen, then update it, and render it.
				act->update();

				// If its a textured actor or polygon, we can render it.

				if (shared_ptr<TexturedActor> ta = dynamic_pointer_cast<TexturedActor>(act)) {

					wc.DrawTexture(*ta->getTexture(), ta->getPosition());
				}else if (shared_ptr<CircleActor> pa = dynamic_pointer_cast<CircleActor>(act)) {
					if (shared_ptr<Enemy> ea = dynamic_pointer_cast<Enemy>(act)) {
						//Radius outline
						//wc.DrawPoly(Circle(pa->getPosition(), 150), LRGB(150, 0, 0), 2);
					}
					wc.DrawFilledPoly(Circle(pa->getPosition(), pa->getRadius()), pa->getFillColour(), pa->getOuterColour(), 2);
					
				}


		}
		if (getPlayer()) {
			string health = string("Health: ") + to_string(getPlayer()->getHealth());
			string score = string("Score: ") + to_string(getScore());
			wc.Write(10, 10, health, LRGB(0, 0, 255));
			wc.Write(10, 23, score, LRGB(0, 0, 255));
		}
	}
	catch (exception &ex) {
		// Had some issues with concurrency, they seem to have went away when i used push_front instead of push_back on the list
		// But better safe than sorry.
		cout << ex.what();
	}
	
}

int SceneManager::getScore() {
	return m_score;
}

void SceneManager::setScore(int score) {
	m_score = score;
}