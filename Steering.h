#include "Enemy.h"
class Steering {

public:
	static VECTOR2  seek(Enemy & act, POINT2 const & t) {
		SCALAR f_max = SCALAR(50);
		SCALAR v_max = SCALAR(50);
		VECTOR2 r = normalise(t - act.getPosition());
		VECTOR2 F = SCALAR(1) * (v_max * r - act.getVelocity());
		if (F.length() > f_max)
			F = f_max * normalise(F);


		return F;
	}

	static VECTOR2  flee(Enemy & act, POINT2 const & t) {
		SCALAR f_max = SCALAR(50);
		SCALAR v_max = SCALAR(50);
		VECTOR2 r = normalise(t - act.getPosition()) * -1;
		VECTOR2 F = SCALAR(1) * (v_max * r - act.getVelocity());
		if (F.length() > f_max)
			F = f_max * normalise(F);


		return F;
	}
};
