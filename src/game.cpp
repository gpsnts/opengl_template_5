#include "headers/game.hpp"

#define BASE_LINE (215.f + 55.47225f)

Renderer *renderer;
Shader selected_shader;

GameObject *player;
GameObject *cloud_1;
GameObject *cactus_1;

const GLfloat PLAYER_VELOCITY(150.f);

Game::~Game()
{
	cout << "Deleting game itens (Renderer, GameObject(s), Shader)" << endl;
	delete renderer;
	delete player, cloud_1;
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
	
	Resources::assign_texture("../src/textures/dino_chrome_spreadsheet_v2.png", GL_TRUE, "character");
	Resources::assign_texture("../src/textures/dino_chrome_floor_compose.png", GL_TRUE, "floor_asset");
	Resources::assign_texture("../src/textures/dino_chrome_cloud.png", GL_TRUE, "cloud_1");
	Resources::assign_texture("../src/textures/dino_chrome_cactus_1.png", GL_TRUE, "cactus_1");

	vec2 PLAYER_SIZE(800, 215);
	vec2 CLOUD_1_SIZE(230, 70);
	vec2 CACTUS_1_SIZE(84, 150);
	
	vec2 player_pos = vec2(
		0,
		(this->ref_height - BASE_LINE)
	);

	vec2 cloud_1_pos(
		this->ref_width - 500,
		125
	);

	vec2 cactus_1_pos = vec2(
		this->ref_width - 450,
		(this->ref_height - (BASE_LINE - 65.f))
	);

	cloud_1 	= new GameObject(Resources::get_texture("cloud_1"), vec2(1.f, 1.f), cloud_1_pos, CLOUD_1_SIZE);
	cactus_1 	= new GameObject(Resources::get_texture("cactus_1"), vec2(1.f, 1.f), cactus_1_pos, CACTUS_1_SIZE);
	player 		= new GameObject(Resources::get_texture("character"), vec2(1.f, 1.f), player_pos, PLAYER_SIZE, 2.f);
}

void Game::handle_input(GLfloat delta, GLint movement, GLboolean action, GLint width, GLint height)
{
	std::cout << "DELTA: " << delta << std::endl;

  GLfloat velocity = PLAYER_VELOCITY * delta;
  if (movement == -1)
    {
      if (player->obj_position.x >= 0) {
        player->obj_position.x -= velocity;
      }
    }
  if (movement == 1)
  {
    if (player->obj_position.x <=  width - player->obj_size.x) {
      player->obj_position.x += velocity;
			player->obj_offset += vec2(1.f / 4.f, 1.f);
    }
  }
}

void Game::update()
{

}

void Game::build()
{
	Texture text_floor;
	text_floor = Resources::get_texture("floor_asset");
	renderer->draw_texture(text_floor, vec2(1.f, 1.f), vec2(0, (this->ref_height - 320)), -1.f, vec2(6000, 320));

	cloud_1->draw(*renderer);
	cactus_1->draw(*renderer);
	player->draw(*renderer);
}