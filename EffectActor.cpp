#include "EffectActor.h"

EffectActor::EffectActor(EffectType effect, std::string file, POINT2 pos) : TexturedActor(file, pos) {
	m_effect = effect;
}