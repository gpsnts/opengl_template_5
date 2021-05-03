#include "headers/resources.hpp"

// Instance (because it's a static)
map<string, Shader>		Resources::shaders;
map<string, Texture> 	Resources::textures;

Shader Resources::assign_shader(
	const char *vertex_shader_file,
	const char *fragment_shader_file,
	string key_shader
)
{
	Shader _shader;
	_shader.compile(vertex_shader_file, fragment_shader_file);
	shaders[key_shader] = _shader;
	return shaders[key_shader];
}

Texture Resources::assign_texture(
	const char *texture_file,
	GLboolean alpha,
	string key_texture
)
{
	textures[key_texture] = load_texture_file(texture_file, alpha);
	return textures[key_texture];
}

Shader Resources::get_shader(string key_shader)
{
	return shaders[key_shader];
}

Texture Resources::get_texture(string key_texture)
{
	return textures[key_texture];
}

void Resources::clean()
{
	for (auto iter_shaders : shaders)
	{
		cout << "Deleting (shader) - " << iter_shaders.first << endl;
		glDeleteProgram(iter_shaders.second.getProgram());
	}

	for (auto iter_textures : textures)
	{
		cout << "Deleting (texture) - " << iter_textures.first << endl;
		glDeleteTextures(1, &iter_textures.second.texture_id);
	}
}

Texture Resources::load_texture_file(string const &file_loc, GLboolean alpha)
{
	Texture texture;
    
	if (alpha)
  {
    texture.internal_format = GL_RGBA;
    texture.image_format 		= GL_RGBA;
  }
  
	int width, height, channels;
  cout << "Loading texture: " << file_loc << endl;
	unsigned char* image;
	
	if (alpha) image = stbi_load(file_loc.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	else image = stbi_load(file_loc.c_str(), &width, &height, &channels,  STBI_rgb);

	if (!image) fprintf(stderr, "%s %s\n", "Failed to Load Texture", file_loc.c_str());

	texture.generate(width, height, image);
  stbi_image_free(image);
  return texture;
}