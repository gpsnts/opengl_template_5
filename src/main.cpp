// Ler o que é definido no cabeçalho "stb_image.h" para entender o porquê disso
#define STB_IMAGE_IMPLEMENTATION

#include "headers/shader.hpp"
#include "headers/resources.hpp"
#include "headers/application.hpp"
#include "headers/game.hpp"

#define CALC_QUAD_WIDTH(x) (x / 2)
#define CALC_QUAD_HEIGHT(y) (y / 2)

int main(int argc, char *argv[])
{
	GLint HEIGHT = 768;
	GLint WIDTH = 1366;
	const GLchar *APP_NAME = "TEST";

	Application *app = new Application(HEIGHT, WIDTH, APP_NAME);
	
	Game *game = new Game(
		HEIGHT, 
		WIDTH
	);

	if (!app->init())
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	bool rotate = false; 

	game->init();

	GLfloat delta 			= 0.f;
  GLfloat last_frame 	= 0.f;
	GLint movement 			= 0;
  GLboolean action 		= false;

	while (!glfwWindowShouldClose(app->get_window()))
	{
		Application::frames_per_second(app->get_window());
		
		Application::process_input(app->get_window());

    // if (glfwGetKey(app->get_window(), GLFW_KEY_LEFT) == GLFW_PRESS) movement = -1;

    if (glfwGetKey(app->get_window(), GLFW_KEY_UP) == GLFW_PRESS) movement = 1;

    // if ((glfwGetKey(app->get_window(), GLFW_KEY_LEFT) != GLFW_PRESS)
		// 		 && (glfwGetKey(app->get_window(), GLFW_KEY_RIGHT) != GLFW_PRESS)) movement = 0;

    // if (glfwGetKey(app->get_window(), GLFW_KEY_SPACE) == GLFW_PRESS) action = true;

		glfwPollEvents();

		GLfloat current = glfwGetTime();
    delta 					= current - last_frame;
    last_frame 			= current;
		
		game->handle_input(delta, movement, action, WIDTH, HEIGHT);

		game->update();

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetFramebufferSize(app->get_window(), &WIDTH, &HEIGHT);

		game->build();
		
		glfwSwapBuffers(app->get_window());
	}

	delete game, app;
	Resources::clean();
	glfwTerminate();

	return EXIT_SUCCESS;
}