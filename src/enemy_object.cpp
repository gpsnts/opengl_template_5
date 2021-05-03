#include "headers/enemy_object.hpp"

void EnemyObject::move(EnemyObject *enemy)
{
	if (!enemy->fixed)
	{
		enemy->obj_position.x -= enemy->obj_velocity.x;

		if (enemy->obj_position.x <= -2999.0f)
		{
			enemy->obj_position.x = 2000.f;
		}
	}
}

void EnemyObject::reset(vec2 position)
{
	this->obj_position = position;
}