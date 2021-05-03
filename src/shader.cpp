#include "headers/shader.hpp"

Shader &Shader::use()
{
	glUseProgram(this->program);
	return *this;
}

void Shader::compile_selected(const char *file_name, GLuint *shader, GLenum type)
{
	FILE *file = fopen(file_name, "r");
	char *content;
	int compile_flag = -1;
	GLchar info_log[512];

	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		size_t file_size = ftell(file);
		rewind(file);

		content = new char[file_size + 1];
		fread(content, sizeof(char), file_size, file);
		content[file_size] = '\0';

		fclose(file);

		// Shader creation
		*shader = glCreateShader(type);
		const GLchar *parsed_content = (const GLchar *)content;
		glShaderSource(*shader, 1, &parsed_content, NULL);
		glCompileShader(*shader);
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &compile_flag);
		// End shader creation

		delete[] content, parsed_content;
	}

	if (GL_TRUE != compile_flag)
	{
		cerr << "ERROR COMPILING " << USED_GL_ENUM(type) << endl;
		glGetShaderInfoLog(*shader, sizeof(info_log), NULL, info_log);
		cerr << "INFO LOG -- " << info_log << endl;
	}
}

void Shader::compile(
	const char *file_name_vertex,
	const char *file_name_fragment
)
{
	GLuint vertex_shader, fragment_shader;
	GLchar info_log[512];

	this->compile_selected(file_name_vertex, &vertex_shader, GL_VERTEX_SHADER);
	this->compile_selected(file_name_fragment, &fragment_shader, GL_FRAGMENT_SHADER);
	
	this->program = glCreateProgram();
	glAttachShader(this->program, vertex_shader);
	glAttachShader(this->program, fragment_shader);

	glLinkProgram(this->program);

	GLint compile_flag = -1;

	glGetProgramiv(this->program, GL_LINK_STATUS, &compile_flag);

	if (GL_TRUE != compile_flag)
	{
		cerr << "ERROR CREATING/LINKING THE PROGRAM" << endl;
		glGetProgramInfoLog(this->program, sizeof(info_log), NULL, info_log);
		cerr << "INFO LOG -- " << info_log << endl;
	}	
}

GLuint Shader::getProgram()
{
	return this->program;
}

void Shader::set_mat4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
  if (useShader) this->use();
  glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, GL_FALSE, value_ptr(matrix));
}

void Shader::set_vec3(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
  if (useShader) this->use();
  glUniform3f(glGetUniformLocation(this->program, name), x, y, z);
}

void Shader::set_vec3(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
  if (useShader) this->use();
  glUniform3f(glGetUniformLocation(this->program, name), value.x, value.y, value.z);
}

void Shader::set_int(const GLchar *name, GLint value, GLboolean useShader)
{
	if (useShader) this->use();
  glUniform1i(glGetUniformLocation(this->program, name), value);
}

void Shader::set_float(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader) this->use();
	glUniform1f(glGetUniformLocation(this->program, name), value);
}

