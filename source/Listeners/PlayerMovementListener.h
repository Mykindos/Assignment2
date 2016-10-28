#pragma once
#include "InputListener.h"
#include <iostream>
class PlayerMovementListener : public InputListener {

public:

	/*
		Handle actor movement
	*/
	virtual void onInput(InputEvent * e) {

		//Downcast to PlayerTank, even though we only pass Actor-PlayerTank in. 
		std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(e->getActor());
		if (player) {
			switch (e->getKey()) {

			case VK_LEFT:

				if (player->getPosition().x < 25) {
					return;
				}

				player->setPosition(POINT2(player->getPosition().x - player->getSpeed(), player->getPosition().y));

				
				break;
			case VK_RIGHT:

				if (player->getPosition().x > 975) {
					return;
				}

				player->setPosition(POINT2(player->getPosition().x + player->getSpeed(), player->getPosition().y));

				
				break;
			case VK_DOWN:
				if (player->getPosition().y > 950) {
					return;
				}

				player->setPosition(POINT2(player->getPosition().x, player->getPosition().y + player->getSpeed()));

				break;

			case VK_UP:
				if (player->getPosition().y < 25) {
					return;
				}
				player->setPosition(POINT2(player->getPosition().x, player->getPosition().y - player->getSpeed()));

				break;
			}
		
	}
	}

	virtual std::string getType() {
		return "InputListener";
	}
};