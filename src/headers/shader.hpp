#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#define USED_GL_ENUM(type) (type == GL_FRAGMENT_SHADER ? "GL_FRAGMENT_SHADER" : "GL_VERTEX_SHADER")

#include <string.h>
#include <stdio.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

using namespace std;
using namespace glm;
class Shader
{
private:
	GLuint program;
	void compile_selected(const char *file_name, GLuint *shader, GLenum type);
public:
	Shader &use();

	void compile(
		const char *file_name_vertex,
		const char *file_name_fragment
	);

	GLuint getProgram();

	// Setters
	void set_int(const GLchar *name, GLint value, GLboolean useShader = false);
	void set_mat4(const GLchar *name, const mat4 &matrix, GLboolean useShader = false);
	void set_vec3(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
  void set_vec3(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void set_float(const GLchar *name, GLfloat value, GLboolean useShader = false);
};

#endif // __SHADER_HPP__