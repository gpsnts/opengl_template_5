#include "headers/game.hpp"

#define BASE_LINE (215.f + 55.47225f)

Renderer *renderer;
Shader selected_shader;

BgObject *bg_floor;

PlayerObject *player;


// GameObject *player;
GameObject *cloud_1;
GameObject *cloud_2;
GameObject *cloud_3;

GameObject *cactus_1;
GameObject *cactus_2;
GameObject *cactus_3;

GameState current = ACTIVE;

const GLfloat PLAYER_VELOCITY(150.f);

Game::~Game()
{
	cout << "Deleting game itens (Renderer, GameObject(s), Shader)" << endl;
	delete renderer;
	delete 	player,
					cactus_1, cactus_2, cactus_3,
					cloud_1, cloud_2, cloud_3;
}

void Game::init()
{
	Resources::assign_shader(
		"../src/shaders/tga.vert",
		"../src/shaders/tga.frag",
		"tga"
	);

	
	mat4 projection = glm::ortho(
		0.0f,
		static_cast<GLfloat>(this->ref_width), 
  	static_cast<GLfloat>(this->ref_height),
		0.0f,
		-1.0f,
		1.0f
	);

	Resources::get_shader("tga").use().set_int("image", 0);
	Resources::get_shader("tga").set_mat4("projection", projection);

	Shader sprite;
	sprite = Resources::get_shader("tga");
	renderer = new Renderer(sprite);
	
	Resources::assign_texture("../src/textures/dino_chrome_spreadsheet_v3.png", GL_TRUE, "character");
	Resources::assign_texture("../src/textures/dino_chrome_floor_compose_v2.png", GL_TRUE, "floor_asset");
	Resources::assign_texture("../src/textures/dino_chrome_cloud.png", GL_TRUE, "cloud_1");
	Resources::assign_texture("../src/textures/dino_chrome_cactus_1.png", GL_TRUE, "cactus_1");

	vec2 PLAYER_SIZE(200, 215);
	vec2 CLOUD_1_SIZE(230, 70);
	vec2 CLOUD_2_SIZE(230, 70);
	vec2 CLOUD_3_SIZE(230, 70);
	vec2 CACTUS_1_SIZE(84, 150);
	
	vec2 player_pos = vec2(
		0,
		(this->ref_height - BASE_LINE)
	);

	vec2 cloud_1_pos(
		this->ref_width + 150,
		rand() % 215 + 1
	);

	vec2 cloud_2_pos(
		this->ref_width + 700,
		rand() % 215 + 1
	);

	vec2 cloud_3_pos(
		this->ref_width + 1975,
		rand() % 215 + 1
	);

	vec2 cactus_1_pos = vec2(
		this->ref_width - 450,
		(this->ref_height - (BASE_LINE - 65.f))
	);

	bg_floor 	= new BgObject(Resources::get_texture("floor_asset"), vec2(0, (this->ref_height - 320)), vec2(6000, 320));

	cloud_1 	= new GameObject(Resources::get_texture("cloud_1"), vec2(0.f, 0.f), cloud_1_pos, 	CLOUD_1_SIZE, 1.f, vec3(1.f), vec2(3.f, 0.f));
	cloud_2 	= new GameObject(Resources::get_texture("cloud_1"), vec2(0.f, 0.f), cloud_2_pos, 	CLOUD_2_SIZE, 1.f, vec3(1.f), vec2(1.5f, 0.f));
	cloud_3 	= new GameObject(Resources::get_texture("cloud_1"), vec2(0.f, 0.f), cloud_3_pos, 	CLOUD_3_SIZE, 1.f, vec3(1.f), vec2(4.f, 0.f));

	cactus_1 	= new GameObject(Resources::get_texture("cactus_1"), 	vec2(0.f, 0.f), cactus_1_pos, CACTUS_1_SIZE);
	player 		=	new PlayerObject(Resources::get_texture("character"), player_pos);
	// player 		= new GameObject(Resources::get_texture("character"), vec2(1.f, 1.f), player_pos, 	PLAYER_SIZE, 2.f);
}

void Game::handle_input(GLfloat delta, GLint movement, GLboolean action, GLint width, GLint height)
{
	GLfloat velocity = PLAYER_VELOCITY * delta;

	if (current == ACTIVE)
	{
		if (movement == 1)
		{
			player->jumping = true;
			player->jump();
		}
	}
}

void Game::update()
{
	std::cout << "FIRST: " << player->obj_position.y << std::endl;
	std::cout << "PLAYER_BASE_LINE: " << PLAYER_BASE_LINE << std::endl;

	if (current == ACTIVE)
	{
		bg_floor->fixed = false;

		cloud_1->obj_position.x -= cloud_1->obj_velocity.x;

		if (cloud_1->obj_position.x <= -5999.0f) {
			cloud_1->obj_position.x = this->ref_width + 15.0f;
			cloud_1->obj_position = vec2(this->ref_width + 150, rand() % 215 + 1);
		}

		cloud_2->obj_position.x -= cloud_2->obj_velocity.x;

		if (cloud_2->obj_position.x <= -5999.0f) {
			cloud_2->obj_position.x = this->ref_width + 15.0f;
			cloud_2->obj_position = vec2(this->ref_width + 700, rand() % 215 + 1);
		}

		cloud_3->obj_position.x -= cloud_3->obj_velocity.x;

		if (cloud_3->obj_position.x <= -5999.0f) {
			cloud_3->obj_position.x = this->ref_width + 15.0f;
			cloud_2->obj_position = vec2(this->ref_width + 1975, rand() % 215 + 1);
		}

		bg_floor->move(bg_floor);
		player->obj_offset += vec2(1.f / 4.f, 1.f);

		this->assert_collisions();
	}
	else
	{
		bg_floor->fixed = true;
	}
}

void Game::build()
{
	bg_floor->draw(*renderer);

	cloud_1->draw(*renderer);
	cloud_2->draw(*renderer);
	cloud_3->draw(*renderer);

	cactus_1->draw(*renderer);
	player->draw(*renderer);
}

GLboolean Game::check_collision(GameObject &a, GameObject &b)
{
	GLboolean collide = a.obj_position.x >= (b.obj_position.x - (b.obj_size.x * 2.45f));
	// string has_collide = collide ? "BATEU": "NAO BATEU";
	// cout 	<< "a.obj_position.x >= b.obj_position.x " 
	// 			<< has_collide << std::endl
	// 			<< "a.obj_position.x: "
	// 			<< a.obj_position.x
	// 			<< " b.obj_position.x: "
	// 			<< b.obj_position.x
	// 			<< " "
	// 			<< std::endl;
	
	return collide;
}

void Game::assert_collisions()
{
	if (check_collision(*player, *cactus_1))
	{
		current = GAME_OVER;
	}
}

