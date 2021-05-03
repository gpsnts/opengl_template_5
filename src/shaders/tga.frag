#version 450 core
in vec2 TexCoords;
out vec4 color;
uniform sampler2D image;
uniform vec3 spriteColor;
uniform float offset_x;
uniform float offset_y;
void main()
{
	vec4 TexColor = vec4(spriteColor, 1.0) * texture(image, vec2(TexCoords.x + offset_x, TexCoords.y + offset_y));
	color = TexColor;
}