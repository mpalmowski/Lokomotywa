#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;

	Vertex(float x, float y, float z)
	{
		pos = glm::vec3(x, y, z);
	}
};

#endif VERTEX_HPP