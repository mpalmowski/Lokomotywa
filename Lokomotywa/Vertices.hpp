#ifndef VERTICES_HPP
#define VERTICES_HPP

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

class Vertices
{
private:
	std::vector<glm::vec3> translateFloatsToVector(std::vector<float> source)
	{
		std::vector<glm::vec3> translated;
		for (int i = 0; i < source.size(); i += 3)
		{
			translated.push_back(glm::vec3(source[i], source[i + 1], source[i + 2]));
		}
		return translated;
	}

public:
	std::vector<float> positions;
	std::vector<float> texture_positions;
	std::vector<unsigned int> indices;
	std::vector<float> normals = {0, 0, 0};

	Vertices(std::vector<float> positions, std::vector<float> texture_positions, std::vector<unsigned int> indices):
		positions(positions), texture_positions(texture_positions), indices(indices)
	{
		calcNormals();
	}

	Vertices() = default;

	void add(Vertices& other, bool calc_normals = true)
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

		if(calc_normals)
			calcNormals();
	}

	void turnInsideOut()
	{
		for(int i = 0; i<indices.size(); i+=3)
		{
			unsigned int temp = indices[i];
			indices[i] = indices[i + 2];
			indices[i + 2] = temp;
		}
	}

	void turnBack()
	{
		for (int i = 0; i<positions.size(); i += 3)
		{
			positions[i + 2] *= -1;
		}

		turnInsideOut();

		calcNormals();
	}

	void moveBy(float x, float y, float z)
	{
		for(int i = 0; i < positions.size(); i += 3)
		{
			positions[i] += x;
			positions[i + 1] += y;
			positions[i + 2] += z;
		}
	}

	void calcNormals()
	{
		std::vector<glm::vec3> normals_vec;
		std::vector<glm::vec3> positions_vec = translateFloatsToVector(positions);

		for (int i = 0; i < positions_vec.size(); ++i)
		{
			normals_vec.push_back(glm::vec3(0, 0, 0));
		}

		for (unsigned int i = 0; i < indices.size(); i += 3)
		{
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];

			glm::vec3 v1 = positions_vec[i1] - positions_vec[i0];
			glm::vec3 v2 = positions_vec[i2] - positions_vec[i0];

			glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

			normals_vec[i0] += normal;
			normals_vec[i1] += normal;
			normals_vec[i2] += normal;
		}

		for (unsigned int i = 0; i < positions_vec.size(); i++)
			normals_vec[i] = glm::normalize(normals_vec[i]);

		normals.clear();
		for (int i = 0; i < normals_vec.size(); i++)
		{
			normals.push_back(normals_vec[i].x);
			normals.push_back(normals_vec[i].y);
			normals.push_back(normals_vec[i].z);
		}
	}
};

#endif
