#include "Figures.h"

Vertices *createRegularPolygon(unsigned int nr_of_vertices, float z, float radius)
{
	std::vector<float> positions = { 0.0, 0.0, z };
	std::vector<float> texture_positions = { 0.5, 0.5 };
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

	return new Vertices(positions, texture_positions, indices);
}

Vertices *createRingPolygon(unsigned int nr_of_vertices, float z, float inner_radius, float radius)
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

	for(unsigned int i=0; i<nr_of_vertices; ++i)
	{
		if (i < nr_of_vertices - 1)
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + nr_of_vertices);

			indices.push_back(i + 1);
			indices.push_back(i + nr_of_vertices);
			indices.push_back(i + nr_of_vertices + 1);
		}
		else
		{
			indices.push_back(i);
			indices.push_back(0);
			indices.push_back(i + nr_of_vertices);

			indices.push_back(0);
			indices.push_back(i + nr_of_vertices);
			indices.push_back(nr_of_vertices);
		}
	}

	return new Vertices(positions, texture_positions, indices);
}