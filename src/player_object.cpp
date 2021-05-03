#include "headers/player_object.hpp"

void PlayerObject::jump()
{
	if (this->obj_position.y > 273.f) this->obj_position.y -= this->obj_velocity.y;
	else if (this->obj_position.y <= 273.f) this->jumping = false;

	else if (!this->jumping && this->obj_position.y != PLAYER_BASE_LINE) this->obj_position.y += this->obj_velocity.y;
}