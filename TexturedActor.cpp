
#include "TexturedActor.h"
#include <iostream>
#include <string>
/*
	Creation of a TexturedActor
	   - Creates WinTexture from file
*/
TexturedActor::TexturedActor(std::string file, POINT2 pos) : Actor(pos) {
	m_texture = std::make_shared<WinTexture>(file, RGB(0,0,0));
}

/*s
	Returns shared_ptr of the Actors Texture, may use  unique_ptr later
*/
std::shared_ptr<WinTexture> TexturedActor::getTexture() {
	return m_texture;
}