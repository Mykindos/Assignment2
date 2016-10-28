#include "ItemActor.h"
class CoinActor : public ItemActor {

public:
	CoinActor(POINT2 pos) : ItemActor("textures//Coin.bmp", pos) {

	}

	virtual ActorType getType() {
		return ActorType::SCORE;
	}

	virtual void update() {

	}

};