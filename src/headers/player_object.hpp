#ifndef __PLAYER_OBJECT_HPP__
#define __PLAYER_OBJECT_HPP__

#define PLAYER_BASE_LINE (497.528f)

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

#include "game_object.hpp"

class PlayerObject : public GameObject
{
public:
	GLboolean fixed = true;
	GLboolean jumping 	=	false;
	GLint jump_frames = 0, movement_controller = 0;
	GLfloat texture_pos_x = 1.f / 4.f;

	PlayerObject()
		: GameObject(), fixed(true) {};

	PlayerObject(Texture sprite, vec2 s_pos, vec2 s_offset = vec2(0.f, 0.f))
	: GameObject(
		sprite,
		s_offset,
		s_pos,
		vec2(200, 215),
		2.f,
		vec3(1.f),
		vec2(0.f, 25.0f)
	), fixed(true)
	{};

	// PlayerObject(vec2 s_pos, Texture sprite, vec2 pos_texture);

	void jump();
	void reset(vec2 pos, vec2 velocity);
};

#endif // __PLAYER_OBJECT_HPP__