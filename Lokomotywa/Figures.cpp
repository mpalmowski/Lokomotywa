#include "Figures.h"

Mesh *createRegularPolygon(unsigned int points)
{
	std::vector<float> positions = { 0.0, 0.0, 0.0 };
	std::vector<float> texture_positions = { 0.5, 0.5 };
	std::vector<unsigned int> indices;

	float alpha = 0;
	float step = 2 * M_PI / points;
	float x, y;

	for (unsigned int i = 1; i <= points; ++i)
	{
		x = sin(alpha);
		y = cos(alpha);

		alpha += step;

		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(0.0);

		x = (x + 1) / 2;
		y = (y + 1) / 2;
		texture_positions.push_back(x);
		texture_positions.push_back(y);

		if (i < points)
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

	return new Mesh(positions, texture_positions, indices);
}