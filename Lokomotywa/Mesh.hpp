#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include  <vector>

class Mesh
{
private:
	enum
	{
		POSITION_VB,
		TEXTURE_POSITION_VB,
		INDICES_VB,
		NUM_BUFFERS
	};

	GLuint vertex_array_object;
	GLuint vertex_array_buffers[NUM_BUFFERS];
	unsigned int draw_count;

public:
	Mesh(std::vector<float> positions, std::vector<float> texture_positions, std::vector<unsigned int> indices)
	{
		draw_count = indices.size();

		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		glGenBuffers(NUM_BUFFERS, vertex_array_buffers);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[TEXTURE_POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, texture_positions.size() * sizeof(float), &texture_positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_array_buffers[INDICES_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

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