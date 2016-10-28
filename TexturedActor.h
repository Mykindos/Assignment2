#pragma once
#include "Actor.h"
#include <iostream>
#include <string>
#include "ui\WinTexture.h"
#include <memory>
class TexturedActor : public Actor {

public:
	TexturedActor(std::string file, POINT2 pos);
	TexturedActor() {
	
	};

	virtual ActorType getType() = 0;
	std::shared_ptr<WinTexture> getTexture();
	virtual void update() = 0;

protected:
	std::shared_ptr<WinTexture> m_texture;
};