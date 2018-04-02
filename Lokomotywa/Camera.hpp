#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

class Camera
{
private:
	float radius;
	
public:
	double alpha_horizontal, alpha_vertical;
	glm::vec3 position;
	glm::mat4 perspective;
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 forward = glm::vec3(0, 0, 1);

	Camera(const glm::vec3 &position, float field_of_view, float aspect, float z_near, float z_far): position(position)
	{
		perspective = glm::perspective(field_of_view, aspect, z_near, z_far);
		radius = std::fabs(position.z);
		alpha_horizontal = M_PI;
		alpha_vertical = M_PI;
	}

	inline glm::mat4 getViewProjection() const
	{
		return perspective * glm::lookAt(position, position + forward, up);
	}

	void moveHorizontallyByAngle(float angle)
	{
		alpha_horizontal += angle;
		if (alpha_horizontal > 2 * M_PI)
			alpha_horizontal -= 2 * M_PI;

		if (alpha_horizontal < 0)
			alpha_horizontal += 2 * M_PI;

		position.x = sin(alpha_horizontal) * radius;
		position.z = cos(alpha_horizontal) * radius;

		forward.x = sin(alpha_horizontal + M_PI);
		forward.z = cos(alpha_horizontal + M_PI);
	}

	void moveVerticallyByAngle(float angle)
	{
		if((angle < 0 && alpha_vertical > M_PI / 2 + angle) || (angle > 0 && alpha_vertical < 3 * M_PI / 2 - angle))
			alpha_vertical += angle;

		position.y = sin(alpha_vertical) * radius;
		position.z = cos(alpha_vertical) * radius;

		forward.y = sin(alpha_vertical + M_PI);
		forward.z = cos(alpha_vertical + M_PI);
	}
};

#endif