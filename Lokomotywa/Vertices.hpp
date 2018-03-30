#ifndef VERTICES_HPP
#define VERTICES_HPP

#include <vector>
#include <iostream>
#include <glm/detail/type_vec3.hpp>

struct Vertices
{
	std::vector<float> positions;
	std::vector<float> texture_positions;
	std::vector<unsigned int> indices;
	std::vector<float> normal;

	Vertices(std::vector<float> positions, std::vector<float> texture_positions, std::vector<unsigned int> indices, std::vector<float> normal = {0, 0, 0}):
		positions(positions), texture_positions(texture_positions), indices(indices), normal(normal)
	{
	}

	Vertices() = default;

	void add(Vertices &other)
	{
		int start_size = indices.size();
		int move = positions.size() / 3;

		positions.insert(positions.end(), other.positions.begin(), other.positions.end());
		texture_positions.insert(texture_positions.end(), other.texture_positions.begin(), other.texture_positions.end());
		indices.insert(indices.end(), other.indices.begin(), other.indices.end());

		for (unsigned int i = start_size; i < indices.size(); ++i)
		{
			indices[i] += move;
		}
	}
};

#endif
