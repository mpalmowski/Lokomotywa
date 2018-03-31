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

	for(unsigned int i = 0; i < nr_of_vertices * 4; ++i)
	{
		connection.texture_positions.push_back((float)(i % nr_of_vertices) / (float)nr_of_vertices);
		if(i < nr_of_vertices * 2)
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
