#include "EffectType.h"
class Effect {

public:
	bool operator== (const Effect & a) const
	{
		return a.getType() == getType() && a.getDuration() == getDuration();
	}


	Effect(EffectType type, long long duration) {
		m_type = type;
		m_duration = duration;
	}

	EffectType getType() const {
		return m_type;
	}

	long long getDuration() const {
		return m_duration;
	}


private:
	EffectType m_type;
	long long m_duration;

};