#ifndef __BG_OBJECT_HPP__
#define __BG_OBJECT_HPP__

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

#include "game_object.hpp"

class BgObject : public GameObject
{
public:
	GLboolean fixed;
	
	BgObject(Texture sprite, vec2 s_pos, vec2 s_size, vec2 s_offset = vec2(0.f, 0.f))
	 : GameObject(
		 sprite,
		 s_offset,
		 s_pos,
		 s_size,
		 1.f,
		 vec3(1.f),
		 vec2(15.f, 0.0f)
	 ), fixed(true)
	{};

	void move(BgObject *bg);
	void reset(vec2 pos, vec2 velocity);	
};

#endif // __BG_OBJECT_HPP__