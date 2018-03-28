#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include  <vector>
#include "Vertex.hpp"

class Mesh
{
private:
	enum
	{
		POSITION_VB,
		TEXTURE_POSITION_VB,
		NUM_BUFFERS
	};

	GLuint vertex_array_object;
	GLuint vertex_array_buffers[NUM_BUFFERS];
	unsigned int draw_count;

public:
	Mesh(Vertex * vertices, unsigned int num_vertices)
	{
		draw_count = num_vertices;

		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texture_positions;

		for (int i = 0; i<num_vertices; i++)
		{
			positions.push_back(vertices[i].position);
			texture_positions.push_back(vertices[i].texture_position);
		}

		glGenBuffers(NUM_BUFFERS, vertex_array_buffers);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[TEXTURE_POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(texture_positions[0]), &texture_positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
	}

	void draw()
	{
		glBindVertexArray(vertex_array_object);

		glDrawArrays(GL_TRIANGLES, 0, draw_count);

		glBindVertexArray(0);
	}
};

#endif MESH_H