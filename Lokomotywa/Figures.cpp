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

Vertices connectedRings(unsigned int nr_of_vertices, float depth, float inner_radius, float radius)
{
	Vertices vertices = ringPolygon(nr_of_vertices, -1 * depth / 2, inner_radius, radius);
	Vertices other = ringPolygon(nr_of_vertices, depth / 2, inner_radius, radius);
	other.turnInsideOut();
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
			connection.texture_positions.push_back(depth);
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

Vertices connectedPolygons(unsigned int nr_of_vertices, float depth, float radius)
{
	Vertices vertices = regularPolygon(nr_of_vertices, -1 * depth / 2, radius);
	Vertices other = regularPolygon(nr_of_vertices, depth / 2, radius);
	other.turnInsideOut();
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
			connection.texture_positions.push_back(depth);
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

Vertices rectangle(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_left, glm::vec3 top_right)
{
	Vertices rect;

	float width, height;

	width = glm::length(glm::vec3(bottom_right - bottom_left));
	height = glm::length(glm::vec3(top_left - bottom_left));

	if(width/height > 10 || width/height < 0.01)
	{
		float min = std::min(width, height);
		width /= min;
		height /= min;
	}
	else if (width > 5 || height > 5)
	{
		width /= 5;
		height /= 5;
	}
	else if (width > 1 || height > 1)
	{
		float max = std::max(width, height);
		width /= max;
		height /= max;
	}

	rect.positions.push_back(bottom_left.x);
	rect.positions.push_back(bottom_left.y);
	rect.positions.push_back(bottom_left.z);

	rect.positions.push_back(bottom_right.x);
	rect.positions.push_back(bottom_right.y);
	rect.positions.push_back(bottom_right.z);

	rect.positions.push_back(top_left.x);
	rect.positions.push_back(top_left.y);
	rect.positions.push_back(top_left.z);

	rect.positions.push_back(top_right.x);
	rect.positions.push_back(top_right.y);
	rect.positions.push_back(top_right.z);

	rect.indices.push_back(0);
	rect.indices.push_back(1);
	rect.indices.push_back(2);

	rect.indices.push_back(2);
	rect.indices.push_back(1);
	rect.indices.push_back(3);

	for (int i = 0; i < 4; ++i)
	{
		rect.texture_positions.push_back((i % 2) * width);

		if (i < 2)
			rect.texture_positions.push_back(height);
		else
			rect.texture_positions.push_back(0);
	}

	rect.calcNormals();
	return rect;
}

Vertices connectedRectangles(glm::vec3 start, glm::vec3 finish, float width, float depth, bool with_top_and_bottom)
{
	Vertices connected_rectangle;

	float height = glm::length(glm::vec3(finish - start));
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

	Vertices rect_front = rectangle(glm::vec3(start_1, start.z + -1 * depth / 2), glm::vec3(start_2, start.z + -1 * depth / 2),
	                                glm::vec3(finish_1, start.z + -1 * depth / 2), glm::vec3(finish_2, start.z + -1 * depth / 2));

	connected_rectangle.add(rect_front, false);

	Vertices rect_right = rectangle(glm::vec3(start_2, start.z + -1 * depth / 2), glm::vec3(start_2, start.z + depth / 2),
	                                glm::vec3(finish_2, start.z + -1 * depth / 2), glm::vec3(finish_2, start.z + depth / 2));

	connected_rectangle.add(rect_right, false);

	Vertices rect_left = rectangle(glm::vec3(start_1, start.z + depth / 2), glm::vec3(start_1, start.z + -1 * depth / 2),
	                               glm::vec3(finish_1, start.z + depth / 2), glm::vec3(finish_1, start.z + -1 * depth / 2));

	connected_rectangle.add(rect_left, false);

	Vertices rect_back = rectangle(glm::vec3(start_2, start.z + depth / 2), glm::vec3(start_1, start.z + depth / 2),
	                               glm::vec3(finish_2, start.z + depth / 2), glm::vec3(finish_1, start.z + depth / 2));

	connected_rectangle.add(rect_back, true);

	if (with_top_and_bottom)
	{
		Vertices rect_top = rectangle(glm::vec3(finish_2, start.z + depth / 2), glm::vec3(finish_1, start.z + depth / 2),
		                              glm::vec3(finish_2, start.z + -1 * depth / 2), glm::vec3(finish_1, start.z + -1 * depth / 2));

		connected_rectangle.add(rect_top, false);

		Vertices rect_bottom = rectangle(glm::vec3(start_1, start.z + depth / 2), glm::vec3(start_2, start.z + depth / 2),
		                                 glm::vec3(start_1, start.z + -1 * depth / 2), glm::vec3(start_2, start.z + -1 * depth / 2));

		connected_rectangle.add(rect_bottom, true);
	}

	return connected_rectangle;
}

Vertices connectedRectangles(glm::vec2 start, glm::vec2 finish, float width, float depth, bool with_top_and_bottom)
{
	return connectedRectangles(glm::vec3(start, 0), glm::vec3(finish, 0), width, depth, with_top_and_bottom);
}

Vertices wheel(unsigned int nr_of_vertices, float depth, float thickness, float nr_of_spokes, float radius)
{
	const float ring_inner_radius = radius - thickness;
	const float inner_circle_radius = 0.3;
	const float inner_circle_thickness = 0.2;
	const float spokes_depth = 0.15;
	const float spokes_width = inner_circle_radius * sin(M_PI / nr_of_spokes);

	Vertices outer = connectedRings(nr_of_vertices, depth / 2, ring_inner_radius, radius);
	outer.moveBy(0, 0, depth / 4);
	Vertices outer2 = connectedRings(nr_of_vertices, depth / 2, ring_inner_radius, radius - thickness / 2);
	outer2.moveBy(0, 0, -depth / 4);
	outer.add(outer2);

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

		x1 = x1 / inner_circle_radius * ring_inner_radius;
		y1 = y1 / inner_circle_radius * ring_inner_radius;
		x2 = x2 / inner_circle_radius * ring_inner_radius;
		y2 = y2 / inner_circle_radius * ring_inner_radius;

		def_x = (x2 - x1) / 4;
		def_y = (y2 - y1) / 4;

		x = x1 + 2 * def_x;
		y = y1 + 2 * def_y;

		spokes_finish.push_back(glm::vec2(x, y));
	}

	for (unsigned int i = 0; i < nr_of_spokes; i++)
	{
		spokes.add(connectedRectangles(spokes_start[i], spokes_finish[i], spokes_width, spokes_depth));
	}

	outer.add(inner);
	outer.add(spokes);

	return outer;
}

Vertices world(unsigned int nr_of_vertices, float radius)
{
	std::vector<float> positions;
	std::vector<float> texture_positions;
	std::vector<unsigned int> indices;

	double alpha_horizontal = 0, alpha_vertical = M_PI / 2;
	float x, y, z;

	for (unsigned int i = 0; i < nr_of_vertices * nr_of_vertices / 4; ++i)
	{
		z = radius * sin(alpha_vertical) * cos(alpha_horizontal);
		x = radius * sin(alpha_vertical) * sin(alpha_horizontal);
		y = radius * cos(alpha_vertical);

		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(z);

		texture_positions.push_back(alpha_horizontal / (2 * M_PI));
		texture_positions.push_back(alpha_vertical / (M_PI / 2));

		alpha_horizontal += 2 * M_PI / nr_of_vertices;

		if (alpha_horizontal >= 2 * M_PI)
		{
			alpha_horizontal = 0;

			z = radius * sin(alpha_vertical) * cos(alpha_horizontal);
			x = radius * sin(alpha_vertical) * sin(alpha_horizontal);
			y = radius * cos(alpha_vertical);

			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);

			texture_positions.push_back(1);
			texture_positions.push_back(alpha_vertical / (M_PI / 2));

			alpha_vertical -= M_PI / 2 / (nr_of_vertices / 4 - 1);

			/*if (alpha_vertical < M_PI / 2 / (nr_of_vertices - 1))
				alpha_vertical = 0;*/
		}
	}

	for (unsigned int i = 0; i < nr_of_vertices; ++i)
	{
		for (unsigned int j = 0; j < nr_of_vertices / 4 - 1; ++j)
		{
			indices.push_back(i + (j + 1) * (nr_of_vertices + 1));
			indices.push_back(i + j * (nr_of_vertices + 1) + 1);
			indices.push_back(i + j * (nr_of_vertices + 1));

			indices.push_back(i + (j + 1) * (nr_of_vertices + 1));
			indices.push_back(i + (j + 1) * (nr_of_vertices + 1) + 1);
			indices.push_back(i + j * (nr_of_vertices + 1) + 1);
		}
	}

	return Vertices(positions, texture_positions, indices);
}
