#include "Figures.h"

Vertices regularPolygon(unsigned int nr_of_vertices, float z, float radius)
{
	std::vector<float> positions = {0.0, 0.0, z};
	std::vector<float> texture_positions = {0.5, 0.5};
	std::vector<unsigned int> indices;

	float alpha = 0;
	float step = 2 * (float)M_PI / nr_of_vertices;
	float x, y;

	for (unsigned int i = 1; i <= nr_of_vertices; ++i)
	{
		x = sin(alpha) * radius;
		y = cos(alpha) * radius;

		alpha += step;

		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(z);

		x = (x + 1) / 2;
		y = (y + 1) / 2;
		texture_positions.push_back(x);
		texture_positions.push_back(y);

		if (i < nr_of_vertices)
		{
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		else
		{
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(1);
		}
	}

	return Vertices(positions, texture_positions, indices);
}

Vertices ringPolygon(unsigned int nr_of_vertices, float z, float inner_radius, float radius)
{
	std::vector<float> positions;
	std::vector<float> texture_positions;
	std::vector<unsigned int> indices;

	float alpha = 0;
	float step = 2 * (float)M_PI / nr_of_vertices;
	float x, y;

	for (unsigned int i = 1; i <= nr_of_vertices; ++i)
	{
		x = sin(alpha) * radius;
		y = cos(alpha) * radius;

		alpha += step;

		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(z);

		x = (x + 1) / 2;
		y = (y + 1) / 2;
		texture_positions.push_back(x);
		texture_positions.push_back(y);
	}

	alpha = 0;

	for (unsigned int i = 1; i <= nr_of_vertices; ++i)
	{
		x = sin(alpha) * inner_radius;
		y = cos(alpha) * inner_radius;

		alpha += step;

		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(z);

		x = (x + 1) / 2;
		y = (y + 1) / 2;
		texture_positions.push_back(x);
		texture_positions.push_back(y);
	}

	for (unsigned int i = 0; i < nr_of_vertices; ++i)
	{
		if (i < nr_of_vertices - 1)
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + nr_of_vertices);

			indices.push_back(i + 1);
			indices.push_back(i + nr_of_vertices + 1);
			indices.push_back(i + nr_of_vertices);
		}
		else
		{
			indices.push_back(i);
			indices.push_back(0);
			indices.push_back(i + nr_of_vertices);

			indices.push_back(0);
			indices.push_back(nr_of_vertices);
			indices.push_back(i + nr_of_vertices);
		}
	}

	return Vertices(positions, texture_positions, indices);
}

Vertices connectedRings(unsigned int nr_of_vertices, float thickness, float inner_radius, float radius)
{
	Vertices vertices = ringPolygon(nr_of_vertices, -1 * thickness / 2, inner_radius, radius);
	Vertices other = ringPolygon(nr_of_vertices, thickness / 2, inner_radius, radius);
	other.turnBack();
	vertices.add(other);

	Vertices connection;

	for (unsigned int i = 0; i < nr_of_vertices * 12; ++i)
	{
		connection.positions.push_back(vertices.positions[i]);
	}

	for (unsigned int i = 0; i < nr_of_vertices * 4; ++i)
	{
		connection.texture_positions.push_back((float)(i % nr_of_vertices) / (float)nr_of_vertices);
		if (i < nr_of_vertices * 2)
		{
			connection.texture_positions.push_back(0);
		}
		else
		{
			connection.texture_positions.push_back(thickness);
		}
	}

	for (unsigned int i = 0; i < nr_of_vertices; ++i)
	{
		if (i < nr_of_vertices - 1)
		{
			connection.indices.push_back(i);
			connection.indices.push_back(i + 2 * nr_of_vertices);
			connection.indices.push_back(i + 1);

			connection.indices.push_back(i + 2 * nr_of_vertices);
			connection.indices.push_back(i + 2 * nr_of_vertices + 1);
			connection.indices.push_back(i + 1);
		}
		else
		{
			connection.indices.push_back(i);
			connection.indices.push_back(i + 2 * nr_of_vertices);
			connection.indices.push_back(0);

			connection.indices.push_back(i + 2 * nr_of_vertices);
			connection.indices.push_back(2 * nr_of_vertices);
			connection.indices.push_back(0);
		}
	}

	for (unsigned int i = nr_of_vertices; i < nr_of_vertices * 2; ++i)
	{
		if (i < 2 * nr_of_vertices - 1)
		{
			connection.indices.push_back(i + 1);
			connection.indices.push_back(i + 2 * nr_of_vertices);
			connection.indices.push_back(i);

			connection.indices.push_back(i + 1);
			connection.indices.push_back(i + 2 * nr_of_vertices + 1);
			connection.indices.push_back(i + 2 * nr_of_vertices);
		}
		else
		{
			connection.indices.push_back(nr_of_vertices);
			connection.indices.push_back(i + 2 * nr_of_vertices);
			connection.indices.push_back(i);

			connection.indices.push_back(nr_of_vertices);
			connection.indices.push_back(3 * nr_of_vertices);
			connection.indices.push_back(i + 2 * nr_of_vertices);
		}
	}

	vertices.add(connection);

	return vertices;
}

Vertices connectedPolygons(unsigned int nr_of_vertices, float thickness, float radius)
{
	Vertices vertices = regularPolygon(nr_of_vertices, -1 * thickness / 2, radius);
	Vertices other = regularPolygon(nr_of_vertices, thickness / 2, radius);
	other.turnBack();
	vertices.add(other);

	Vertices connection;

	for (unsigned int i = 3; i < nr_of_vertices * 6 + 6; i += 3)
	{
		if (i != 3 * nr_of_vertices + 3)
		{
			connection.positions.push_back(vertices.positions[i]);
			connection.positions.push_back(vertices.positions[i + 1]);
			connection.positions.push_back(vertices.positions[i + 2]);
		}
	}

	for (unsigned int i = 0; i < nr_of_vertices * 2; ++i)
	{
		connection.texture_positions.push_back((float)(i % nr_of_vertices) / (float)nr_of_vertices);
		if (i < nr_of_vertices)
		{
			connection.texture_positions.push_back(0);
		}
		else
		{
			connection.texture_positions.push_back(thickness);
		}
	}

	for (unsigned int i = 0; i < nr_of_vertices; ++i)
	{
		if (i < nr_of_vertices - 1)
		{
			connection.indices.push_back(i);
			connection.indices.push_back(i + nr_of_vertices);
			connection.indices.push_back(i + 1);

			connection.indices.push_back(i + nr_of_vertices);
			connection.indices.push_back(i + nr_of_vertices + 1);
			connection.indices.push_back(i + 1);
		}
		else
		{
			connection.indices.push_back(i);
			connection.indices.push_back(i + nr_of_vertices);
			connection.indices.push_back(0);

			connection.indices.push_back(i + nr_of_vertices);
			connection.indices.push_back(nr_of_vertices);
			connection.indices.push_back(0);
		}
	}

	vertices.add(connection);

	return vertices;
}

Vertices square(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_left, glm::vec3 top_right)
{
	Vertices square;

	float width, height;

	width = glm::length(glm::vec3(bottom_right - bottom_left));
	height = glm::length(glm::vec3(top_left - bottom_left));

	square.positions.push_back(bottom_left.x);
	square.positions.push_back(bottom_left.y);
	square.positions.push_back(bottom_left.z);

	square.positions.push_back(bottom_right.x);
	square.positions.push_back(bottom_right.y);
	square.positions.push_back(bottom_right.z);

	square.positions.push_back(top_left.x);
	square.positions.push_back(top_left.y);
	square.positions.push_back(top_left.z);

	square.positions.push_back(top_right.x);
	square.positions.push_back(top_right.y);
	square.positions.push_back(top_right.z);

	square.indices.push_back(0);
	square.indices.push_back(1);
	square.indices.push_back(2);

	square.indices.push_back(2);
	square.indices.push_back(1);
	square.indices.push_back(3);

	for (int i = 0; i < 8; ++i)
	{
		if (i < 2)
			square.texture_positions.push_back(0);
		else
			square.texture_positions.push_back(height);

		square.texture_positions.push_back((i % 2) * width);
	}

	return square;
}

Vertices plank(glm::vec2 start, glm::vec2 finish, float width, float depth)
{
	Vertices plank;

	float height = sqrt(pow(finish.x - start.x, 2) + pow(finish.y - start.y, 2));
	float ratio = width / height;

	glm::vec2 start_1, start_2, finish_1, finish_2;
	start_1.x = start.x + (finish.y - start.y) * ratio / 2;
	start_1.y = start.y - (finish.x - start.x) * ratio / 2;
	start_2.x = start.x - (finish.y - start.y) * ratio / 2;
	start_2.y = start.y + (finish.x - start.x) * ratio / 2;

	finish_1.x = finish.x + (finish.y - start.y) * ratio / 2;
	finish_1.y = finish.y - (finish.x - start.x) * ratio / 2;
	finish_2.x = finish.x - (finish.y - start.y) * ratio / 2;
	finish_2.y = finish.y + (finish.x - start.x) * ratio / 2;

	Vertices square_front = square(glm::vec3(start_1, -1 * depth / 2), glm::vec3(start_2, -1 * depth / 2),
	                               glm::vec3(finish_1, -1 * depth / 2), glm::vec3(finish_2, -1 * depth / 2));

	Vertices square_right = square(glm::vec3(start_2, -1 * depth / 2), glm::vec3(start_2, depth / 2),
	                               glm::vec3(finish_2, -1 * depth / 2), glm::vec3(finish_2, depth / 2));

	Vertices square_left = square(glm::vec3(start_1, depth / 2), glm::vec3(start_1, -1 * depth / 2),
	                              glm::vec3(finish_1, depth / 2), glm::vec3(finish_1, -1 * depth / 2));

	Vertices square_back = square(glm::vec3(start_2, depth / 2), glm::vec3(start_1, depth / 2),
	                              glm::vec3(finish_2, depth / 2), glm::vec3(finish_1, depth / 2));

	plank.add(square_front);
	plank.add(square_right);
	plank.add(square_left);
	plank.add(square_back);

	return plank;
}

Vertices wheel(unsigned int nr_of_vertices, float thickness, float nr_of_spokes)
{
	const float ring_inner_radius = 0.8;
	const float inner_circle_radius = 0.3;
	const float inner_circle_thickness = 0.2;
	const float spokes_depth = 0.15;
	const float spokes_width = inner_circle_radius * sin(M_PI / nr_of_spokes);

	Vertices outer = connectedRings(nr_of_vertices, thickness, ring_inner_radius);
	Vertices inner = connectedPolygons(nr_of_vertices, inner_circle_thickness, inner_circle_radius);
	Vertices spokes;

	std::vector<glm::vec2> spokes_start;
	std::vector<glm::vec2> spokes_finish;

	float x1, x2, y1, y2;
	float x, y;
	float def_x, def_y;

	float step = 2 * (float)M_PI / nr_of_spokes;
	float alpha = 0;

	for (unsigned int i = 0; i < nr_of_spokes; ++i)
	{
		x1 = sin(alpha) * inner_circle_radius;
		y1 = cos(alpha) * inner_circle_radius;

		alpha += step;

		x2 = sin(alpha) * inner_circle_radius;
		y2 = cos(alpha) * inner_circle_radius;

		def_x = (x2 - x1) / 4;
		def_y = (y2 - y1) / 4;

		x = x1 + 2 * def_x;
		y = y1 + 2 * def_y;

		spokes_start.push_back(glm::vec2(x, y));

		x1 = x1 / inner_circle_radius;
		y1 = y1 / inner_circle_radius;
		x2 = x2 / inner_circle_radius;
		y2 = y2 / inner_circle_radius;

		def_x = (x2 - x1) / 4;
		def_y = (y2 - y1) / 4;

		x = x1 + 2 * def_x;
		y = y1 + 2 * def_y;

		spokes_finish.push_back(glm::vec2(x, y));
	}

	for (unsigned int i = 0; i < nr_of_spokes; i++)
	{
		spokes.add(plank(spokes_start[i], spokes_finish[i], spokes_width, spokes_depth));
	}

	outer.add(inner);
	outer.add(spokes);

	return outer;
}
