#include "headers/player_object.hpp"

void PlayerObject::jump()
{
	std::cout << "PUlando" << std::endl;
	if (this->jumping)
	{
		if (this->obj_position.y > PLAYER_MAX_HEIGHT) this->obj_position.y -= this->obj_velocity.y;
	}
}