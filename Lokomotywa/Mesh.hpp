#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertices.hpp"

class Mesh
{
private:
	enum
	{
		POSITION_VB,
		TEXTURE_POSITION_VB,
		INDICES_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};

	GLuint vertex_array_object;
	GLuint vertex_array_buffers[NUM_BUFFERS];
	unsigned int draw_count;

public:
	Mesh(Vertices vertices)
	{
		draw_count = vertices.indices.size();

		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		glGenBuffers(NUM_BUFFERS, vertex_array_buffers);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, vertices.positions.size() * sizeof(float), &vertices.positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[TEXTURE_POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, vertices.texture_positions.size() * sizeof(float), &vertices.texture_positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_array_buffers[INDICES_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.indices.size() * sizeof(unsigned int), &vertices.indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, vertices.normals.size() * sizeof(float), &vertices.normals[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
	}

	void draw()
	{
		glBindVertexArray(vertex_array_object);

		glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(0);
	}
};

#endif MESH_H