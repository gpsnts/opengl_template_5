#include "headers/bg_object.hpp"

void BgObject::move(BgObject *bg)
{
	if (!bg->fixed) {
		bg->obj_position.x -= bg->obj_velocity.x;

		if (bg->obj_position.x <= -3999.0f) {
			bg->obj_position.x = 0.0f;
		}
	}
}

void BgObject::reset(vec2 pos, vec2 velocity)
{
	this->obj_position 	= pos;
	this->obj_velocity 	= velocity;
	this->fixed					= true;
}