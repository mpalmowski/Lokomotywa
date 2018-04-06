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
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 forward = glm::vec3(0, 0, 1);
	
public:
	double alpha_horizontal, alpha_vertical;
	glm::vec3 position;
	glm::mat4 perspective;

	Camera(const glm::vec3 &position, float field_of_view, float aspect, float z_near, float z_far): position(position)
	{
		perspective = glm::perspective(field_of_view, aspect, z_near, z_far);
		radius = std::fabs(position.z);
		alpha_horizontal = M_PI;
		alpha_vertical = M_PI / 2;
		calculatePosiiton();
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

		calculatePosiiton();
	}

	void moveVerticallyByAngle(float angle)
	{
		if((angle < 0 && alpha_vertical > angle) || (angle > 0 && alpha_vertical < M_PI - angle))
			alpha_vertical += angle;

		calculatePosiiton();
	}

	void moveAlongRadius(float step)
	{
		if(step > 0 || step < 0 && radius > 1 + step)
			radius += step;

		calculatePosiiton();
	}

	void calculatePosiiton()
	{
		position.z = radius * sin(alpha_vertical) * cos(alpha_horizontal);
		position.x = radius * sin(alpha_vertical) * sin(alpha_horizontal);
		position.y = radius * cos(alpha_vertical);

		forward.z = -1 * position.z;
		forward.x = -1 * position.x;
		forward.y = -1 * position.y;
	}
};

#endif