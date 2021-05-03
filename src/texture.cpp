#include "headers/texture.hpp"
#include <iostream>

void Texture::generate(GLuint width, GLuint height, unsigned char* data)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
 
  glTexImage2D(
		GL_TEXTURE_2D,
		0,
		this->internal_format,
		width, height,
		0,
		this->image_format,
		GL_UNSIGNED_BYTE,
		data
	);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}