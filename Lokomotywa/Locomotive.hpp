#ifndef LOCOMOTIVE_HPP
#define LOCOMOTIVE_HPP

#include "Vertices.hpp"
#include "Figures.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "RenderedObject.hpp"

const unsigned int WHEEL_VERTICES = 80;
const float WHEEL_DEPTH = 0.25;
const float WHEEL_THICKNESS = 0.2;
const unsigned int NR_OF_WHEEL_SPOKES = 16;

const float WHEEL_BASE = 4;
const float TRACK_WIDTH = 2.5;

const float BAR_WIDTH = 0.15;
const float BAR_DEPTH = 0.1;

const float WHEEL_ROT_SPEED = 0.003;

const unsigned int NR_OF_WHEELS = 4;

class Locomotive
{
private:
	RenderedObject* wheels[NR_OF_WHEELS];
	RenderedObject* bar[2];
	RenderedObject* chassis;
public:
	Locomotive()
	{
		for (unsigned int i = 0; i < NR_OF_WHEELS; ++i)
		{
			wheels[i] = new RenderedObject(wheel(WHEEL_VERTICES, WHEEL_DEPTH, WHEEL_THICKNESS, NR_OF_WHEEL_SPOKES), "red_painted_metal.png");

			if (i < NR_OF_WHEELS / 2)
			{
				wheels[i]->moveBy(WHEEL_BASE / 2 - i % (NR_OF_WHEELS / 2) * WHEEL_BASE / ((NR_OF_WHEELS - 1) / 2), 0,
				                  -1 * TRACK_WIDTH / 2);
			}
			else
			{
				wheels[i]->moveBy(WHEEL_BASE / 2 - i % (NR_OF_WHEELS / 2) * WHEEL_BASE / ((NR_OF_WHEELS - 1) / 2), 0,
				                  TRACK_WIDTH / 2);
			}
		}

		chassis = new RenderedObject(connectedRectangles(glm::vec2(-1 * WHEEL_BASE / 2 - 1, 0), glm::vec2(WHEEL_BASE / 2 + 1, 0),
		                                                 0.5, TRACK_WIDTH - WHEEL_DEPTH, true), "green_planks.jpg");

		bar[0] = new RenderedObject(connectedRectangles(glm::vec2(-1 * WHEEL_BASE / 2, 0), glm::vec2(WHEEL_BASE / 2, 0), BAR_WIDTH, BAR_DEPTH, true), "red_painted_metal.png");
		bar[1] = new RenderedObject(connectedRectangles(glm::vec2(-1 * WHEEL_BASE / 2, 0), glm::vec2(WHEEL_BASE / 2, 0), BAR_WIDTH, BAR_DEPTH, true), "red_painted_metal.png");
		bar[0]->moveBy(0, 1 - WHEEL_THICKNESS / 2, -1 * (TRACK_WIDTH + WHEEL_DEPTH + BAR_DEPTH) / 2);
		bar[1]->moveBy(0, 1 - WHEEL_THICKNESS / 2, (TRACK_WIDTH + WHEEL_DEPTH + BAR_DEPTH) / 2);
	}

	~Locomotive()
	{
		for (unsigned int i = 0; i < NR_OF_WHEELS; ++i)
		{
			delete wheels[i];
		}
		delete chassis;
	}

	void draw(Shader& shader, Camera& camera)
	{
		unsigned int texture_unit = 0;

		for (unsigned int i = 0; i < NR_OF_WHEELS; i++)
		{
			wheels[i]->draw(texture_unit, shader, camera);
			texture_unit++;

			wheels[i]->rotateBy(0, 0, WHEEL_ROT_SPEED);
		}

		chassis->draw(texture_unit, shader, camera);
		texture_unit++;

		for(int i = 0; i < 2; ++i)
		{
			bar[i]->draw(texture_unit, shader, camera);
			texture_unit++;

			bar[i]->moveInCircleByAngle(WHEEL_ROT_SPEED, 1 - WHEEL_THICKNESS / 2);
		}
	}
};

#endif
