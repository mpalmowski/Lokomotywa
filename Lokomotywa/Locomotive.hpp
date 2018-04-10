#ifndef LOCOMOTIVE_HPP
#define LOCOMOTIVE_HPP

#include "Vertices.hpp"
#include "Figures.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "RenderedObject.hpp"

const unsigned int WHEEL_VERTICES = 80;
const float WHEEL_THICKNESS = 0.25;
const unsigned int NR_OF_WHEEL_SPOKES = 20;

const float WHEEL_BASE = 4;
const float TRACK_WIDTH = 2.5;

const float WHEEL_ROT_SPEED = 0.0015;

const unsigned int NR_OF_WHEELS = 4;

class Locomotive
{
private:
	RenderedObject* wheels[NR_OF_WHEELS];
	RenderedObject* bar;
	RenderedObject* chassis;
public:
	Locomotive()
	{
		for (unsigned int i = 0; i < NR_OF_WHEELS; ++i)
		{
			wheels[i] = new RenderedObject(wheel(WHEEL_VERTICES, WHEEL_THICKNESS, NR_OF_WHEEL_SPOKES), "red_painted_metal.png");

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
		                                                 0.5,
		                                                 TRACK_WIDTH - WHEEL_THICKNESS, true), "green_planks.jpg");
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
		for (unsigned int i = 0; i < NR_OF_WHEELS; i++)
		{
			wheels[i]->draw(i, shader, camera);

			wheels[i]->rotateBy(0, 0, WHEEL_ROT_SPEED);
		}

		chassis->draw(NR_OF_WHEELS, shader, camera);
	}
};

#endif
