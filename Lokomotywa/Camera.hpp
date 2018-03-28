#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
	glm::vec3 position;
	glm::mat4 perspective;
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 forward = glm::vec3(0, 0, 1);

	Camera(const glm::vec3 &position, float field_of_view, float aspect, float z_near, float z_far): position(position)
	{
		perspective = glm::perspective(field_of_view, aspect, z_near, z_far);
	}

	inline glm::mat4 getViewProjection() const
	{
		return perspective * glm::lookAt(position, position + forward, up);
	}
};

#endif