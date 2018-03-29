#ifndef VERTICES_HPP
#define VERTICES_HPP

#include <vector>
#include <iostream>

struct Vertices
{
	std::vector<float> positions;
	std::vector<float> texture_positions;
	std::vector<unsigned int> indices;

	Vertices(std::vector<float> positions, std::vector<float> texture_positions, std::vector<unsigned int> indices):
		positions(positions), texture_positions(texture_positions), indices(indices)
	{
	}

	Vertices& operator+= (Vertices &other)
	{
		int start_size = indices.size();
		int move = positions.size() / 3;

		positions.insert(positions.end(), other.positions.begin(), other.positions.end());
		texture_positions.insert(texture_positions.end(), other.texture_positions.begin(), other.texture_positions.end());
		indices.insert(indices.end(), other.indices.begin(), other.indices.end());

		for(int i = start_size; i < indices.size(); ++i)
		{
			indices[i] += move;
		}

		return *this;
	}
};

#endif
