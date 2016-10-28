#pragma once
#include <iostream>
#include <list>
#include "Enemy.h"
#include "ui/WinCanvas.h"
#include "Player.h"

class SceneManager {
	static SceneManager * instance;


public:


	/*
	Singleton getter
	*/
	static SceneManager *getInstance() {
		if (!instance) {
			instance = new SceneManager();
		}
		return instance;
	}

	std::list<std::shared_ptr<Enemy>> & getEnemyPool() {
		return enemyPool;
	}

	void createPlayer(std::shared_ptr<Player> t);
	void removeActor(std::shared_ptr<Actor> act);
	void addActor(ActorType t);
	void addEffectActor(EffectType effect);
	std::shared_ptr<Player> getPlayer();

	void loadScene();
	void addEnemies();
	void addItems();
	void healPlayer();
	void processInput(char c);
	void processCollisions();
	void setScore(int score);
	int getScore();
	std::list<std::shared_ptr<Actor>> & getActors();
	std::list<std::shared_ptr<Actor>> & getPendingRemoval();
	double distance(Actor & a, Actor & b);
	
	// We want to update the existing WinCanvas, so pass by reference
	void updateActors(WinCanvas & wc);

private:

	std::list<std::shared_ptr<Actor>> actors;
	std::shared_ptr<Player> player;
	std::list<std::shared_ptr<Enemy>> enemyPool;
	std::list<std::shared_ptr<Actor>> pendingRemoval;
	long long lastEnemy, lastItem, lastHeal;
	int m_score = 0;
};