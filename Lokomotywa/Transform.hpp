#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Transform
{
	glm::vec3 position, rotation, scale;

	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(),
	          const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0)): position(position), rotation(rotation), scale(scale)
	{}

	inline glm::mat4 getModel() const
	{
		glm::mat4 position_matrix = glm::translate(position);
		glm::mat4 scale_matrix = glm::scale(scale);

		glm::mat4 rotation_x_matrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotation_y_matrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotation_z_matrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 rotation_matrix = rotation_z_matrix * rotation_y_matrix * rotation_x_matrix;

		return position_matrix * rotation_matrix * scale_matrix;
	}
};

#endif
