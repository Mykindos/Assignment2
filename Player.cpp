#include "Player.h"
#include <iostream>
#include <string>
#include <chrono>
#include <random>


using namespace std;
using namespace chrono;


Player::Player(double radius, long fillColour, long outerColour, POINT2 pos, double speed) : CircleActor(radius, fillColour, outerColour, pos) {
	m_speed = speed;
	// TODO stuff
}


void Player::update() {
	
}

int Player::getHealth() {
	return m_health;
}

int Player::getMaxHealth() {
	return m_maxHealth;
}

void Player::setHealth(int health) {
	m_health = health;
}

void Player::setMaxHealth(int maxHealth) {
	m_maxHealth = maxHealth;
}

double Player::getSpeed() {
	return m_speed;
}


ActorType Player::getType() {
	return ActorType::PLAYER;
}