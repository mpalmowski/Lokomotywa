#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.hpp"

class Mesh
{
private:
	enum
	{
		POSITION_VB,
		NUM_BUFFERS
	};

	GLuint vertex_array_object;
	GLuint vertex_array_buffers[NUM_BUFFERS];
	unsigned int draw_count;

public:
	Mesh(Vertex *vertices, unsigned int num_vertices);
	~Mesh();
	void draw();
};

#endif MESH_H