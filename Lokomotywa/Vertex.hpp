#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texture_position;

	Vertex(float x, float y, float z, float tex_x, float tex_y)
	{
		position = glm::vec3(x, y, z);
		texture_position = glm::vec2(tex_x, tex_y);
	}
};

#endif VERTEX_HPP