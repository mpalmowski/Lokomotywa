#ifndef LOCOMOTIVE_HPP
#define LOCOMOTIVE_HPP

#include "Vertices.hpp"
#include "Figures.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "RenderedObject.hpp"

const unsigned int WHEEL_VERTICES = 80;
const float WHEEL_RADIUS = 1;
const float WHEEL_DEPTH = 0.25;
const float WHEEL_THICKNESS = 0.2;
const unsigned int NR_OF_WHEEL_SPOKES = 16;

const float WHEELBASE = 4;
const float TRACK_WIDTH = 2.5;

const float BAR_WIDTH = 0.15;
const float BAR_DEPTH = 0.1;

const float GROUND_WIDTH = 20;
const float GROUND_LENGTH = 1000;
const float WALL_HEIGHT = 5;

const float WHEEL_ROT_SPEED = 0.005;
const float LOCOMOTIVE_SPEED = 2 * M_PI * WHEEL_RADIUS / (2 * M_PI / WHEEL_ROT_SPEED);

const unsigned int NR_OF_WHEELS = 4;

class Locomotive
{
private:
	RenderedObject* wheels[NR_OF_WHEELS];
	RenderedObject* bar[2];
	RenderedObject* chassis;
	RenderedObject* ground[2];
	RenderedObject* walls[4];
	RenderedObject* sky;

	Shader* sky_shader;
public:
	Locomotive()
	{
		for (unsigned int i = 0; i < NR_OF_WHEELS; ++i)
		{
			wheels[i] = new RenderedObject(wheel(WHEEL_VERTICES, WHEEL_DEPTH, WHEEL_THICKNESS, NR_OF_WHEEL_SPOKES, WHEEL_RADIUS),
			                               "red_painted_metal.png");

			if (i < NR_OF_WHEELS / 2)
			{
				wheels[i]->moveBy(WHEELBASE / 2 - i % (NR_OF_WHEELS / 2) * WHEELBASE / ((NR_OF_WHEELS - 1) / 2), 0,
				                  -1 * TRACK_WIDTH / 2);
			}
			else
			{
				wheels[i]->moveBy(WHEELBASE / 2 - i % (NR_OF_WHEELS / 2) * WHEELBASE / ((NR_OF_WHEELS - 1) / 2), 0,
				                  TRACK_WIDTH / 2);
			}
		}

		chassis = new RenderedObject(connectedRectangles(glm::vec2(-1 * WHEELBASE / 2 - WHEEL_RADIUS, 0),
		                                                 glm::vec2(WHEELBASE / 2 + WHEEL_RADIUS, 0),
		                                                 0.5, TRACK_WIDTH - WHEEL_DEPTH, true), "green_planks.jpg");

		bar[0] = new RenderedObject(
			connectedRectangles(glm::vec2(-1 * WHEELBASE / 2, 0), glm::vec2(WHEELBASE / 2, 0), BAR_WIDTH, BAR_DEPTH, true),
			"red_painted_metal.png");
		bar[1] = new RenderedObject(
			connectedRectangles(glm::vec2(-1 * WHEELBASE / 2, 0), glm::vec2(WHEELBASE / 2, 0), BAR_WIDTH, BAR_DEPTH, true),
			"red_painted_metal.png");
		bar[0]->moveBy(0, 1 - WHEEL_THICKNESS / 2, -1 * (TRACK_WIDTH + WHEEL_DEPTH + BAR_DEPTH) / 2);
		bar[1]->moveBy(0, 1 - WHEEL_THICKNESS / 2, (TRACK_WIDTH + WHEEL_DEPTH + BAR_DEPTH) / 2);

		createGround();
		createWalls();

		sky = new RenderedObject(world(80, 500), "sky_povray.jpg");
		sky->moveBy(0, -WHEEL_RADIUS, 0);

		sky_shader = new Shader("sky_shader");
	}

	void createGround()
	{
		for (int i = 0; i < 2; ++i)
		{
			ground[i] = new RenderedObject(rectangle(glm::vec3(-GROUND_LENGTH / 2, 0, -GROUND_LENGTH / 2),
				glm::vec3(-GROUND_LENGTH / 2, 0, GROUND_LENGTH / 2),
				glm::vec3(GROUND_LENGTH / 2, 0, -GROUND_LENGTH / 2),
				glm::vec3(GROUND_LENGTH / 2, 0, GROUND_LENGTH / 2)), "grass.jpg");

			if (i == 0)
				ground[i]->moveBy(-GROUND_LENGTH, 0, 0);

			ground[i]->moveBy(0, -WHEEL_RADIUS, 0);
		}
	}

	void createWalls()
	{
		int side = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (i < 2)
				side = -1;
			else
				side = 1;

			walls[i] = new RenderedObject(rectangle(glm::vec3(-GROUND_LENGTH / 2, 0, side * GROUND_WIDTH / 2),
				glm::vec3(GROUND_LENGTH / 2, 0, side * GROUND_WIDTH / 2),
				glm::vec3(-GROUND_LENGTH / 2, WALL_HEIGHT, side * GROUND_WIDTH / 2),
				glm::vec3(GROUND_LENGTH / 2, WALL_HEIGHT, side * GROUND_WIDTH / 2)), "ivy.jpg", true);

			if (i%2 == 0)
				walls[i]->moveBy(-GROUND_LENGTH, 0, 0);

			walls[i]->moveBy(0, -WHEEL_RADIUS, 0);
		}
	}

	void moveGroundandWalls()
	{
		for(int i = 0; i<2; ++i)
		{
			ground[i]->moveBy(LOCOMOTIVE_SPEED, 0, 0);
		}

		for (int i = 0; i<4; ++i)
		{
			walls[i]->moveBy(LOCOMOTIVE_SPEED, 0, 0);
		}

		if (ground[1]->getPosition().x >= GROUND_LENGTH)
		{
			std::swap(ground[0], ground[1]);
			ground[0]->moveBy(-2 * GROUND_LENGTH, 0, 0);

			std::swap(walls[0], walls[1]);
			std::swap(walls[2], walls[3]);
			walls[0]->moveBy(-2 * GROUND_LENGTH, 0, 0);
			walls[2]->moveBy(-2 * GROUND_LENGTH, 0, 0);
		}
	}

	~Locomotive()
	{
		for (unsigned int i = 0; i < NR_OF_WHEELS; ++i)
		{
			delete wheels[i];
		}

		delete chassis;

		for (int i = 0; i < 2; i++)
		{
			delete bar[i];
		}

		delete sky_shader;
	}

	void draw(Shader& shader, Camera& camera)
	{
		unsigned int texture_unit = 0;

		for (unsigned int i = 0; i < NR_OF_WHEELS; i++)
		{
			wheels[i]->draw(texture_unit, shader, camera);

			wheels[i]->rotateBy(0, 0, WHEEL_ROT_SPEED);
		}

		chassis->draw(texture_unit++, shader, camera);

		for (int i = 0; i < 2; ++i)
		{
			bar[i]->draw(texture_unit, shader, camera);

			bar[i]->moveInCircleByAngle(WHEEL_ROT_SPEED, WHEEL_RADIUS - WHEEL_THICKNESS / 2);
		}

		for(int i = 0; i < 2; ++i)
			ground[i]->draw(texture_unit, shader, camera);

		moveGroundandWalls();

		for (int i = 0; i < 4; ++i)
			walls[i]->draw(texture_unit, shader, camera);

		sky->draw(texture_unit++, *sky_shader, camera);
	}
};

#endif
