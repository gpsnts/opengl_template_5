#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>

#include "game_object.hpp"
#include "bg_object.hpp"
#include "enemy_object.hpp"
#include "player_object.hpp"
#include "shader.hpp"
#include "renderer.hpp"
#include "resources.hpp"

enum GameState {
	ACTIVE,
	GAME_OVER
};

class Game
{
private:
	GLint ref_height, ref_width;
public:
	~Game();
	Game(
		GLint s_height,
		GLint s_width
	) {
		this->ref_height = s_height;
		this->ref_width = s_width;
	};

	void handle_input(GLfloat delta, GLint movement, GLboolean action, GLint width, GLint height);

	void init();
	void build();
	void update();

	GLboolean check_collision(GameObject &a, GameObject &b);
	void assert_collisions();
};

#endif // __GAME_HPP__
