#pragma once
#include "PolygonActor.h"

class CircleActor : public PolygonActor {

public:
	CircleActor(double radius, long fillColour, long outerColour, POINT2 pos) : PolygonActor(fillColour, outerColour, pos) {
		m_radius = radius;
	}

	virtual ActorType getType() = 0;
	virtual void update() = 0;

	double getRadius() {
		return m_radius;
	}

private:
	double m_radius = 0;

};