#ifndef __ENEMY_OBJECT_HPP__
#define __ENEMY_OBJECT_HPP__

#include "game_object.hpp"

class EnemyObject : public GameObject
{
public:
	GLboolean fixed;

	EnemyObject(Texture sprite, vec2 s_pos, vec2 s_size, vec2 s_offset = vec2(0.f, 0.f))
		: GameObject(sprite, s_offset, s_pos, s_size, 1.f, vec3(1.f), vec2(15.f, 0)),
			fixed(false) {};

	void move(EnemyObject *enemy);
	void reset(vec2 position);
};

#endif // !__ENEMY_OBJECT_HPP__