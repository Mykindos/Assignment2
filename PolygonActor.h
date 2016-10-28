#include "Actor.h"
#define LRGB(r,g,b)          ((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))


class PolygonActor : public Actor {

public:
	PolygonActor(long fillColour, long outerColour, POINT2 pos) : Actor(pos) {
		m_fillColour = fillColour;
		m_outerColour = outerColour;
	}

	PolygonActor() {

	};

	virtual ActorType getType() = 0;
	virtual void update() = 0;



	long getFillColour() {
		return m_fillColour;
	}

	long getOuterColour() {
		return m_outerColour;
	}
private:

	long m_fillColour = LRGB(0, 0, 0);
	long m_outerColour = LRGB(0, 0, 0);
};