#ifndef LOCOMOTIVE_HPP
#define LOCOMOTIVE_HPP

#include "Vertices.hpp"
#include "Figures.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "RenderedObject.hpp"

const unsigned int WHEEL_VERTICES = 40;
const float WHEEL_RADIUS = 1;
const float WHEEL_DEPTH = 0.25;
const float WHEEL_THICKNESS = 0.2;
const unsigned int NR_OF_WHEEL_SPOKES = 16;
const unsigned int NR_OF_WHEELS = 6;

const float WHEELBASE = (NR_OF_WHEELS - 2) * (WHEEL_RADIUS + WHEEL_RADIUS / 10);
const float TRACK_WIDTH = 2.5;

const float BAR_WIDTH = 0.15;
const float BAR_DEPTH = 0.1;
const float BAR_POS_RADIUS = WHEEL_RADIUS / 2;

const float GROUND_WIDTH = 20;
const float GROUND_LENGTH = 1000;

const float RAILS_HEIGHT = 0.1;

const float RAIL_PLANK_HEIGHT = 0.1;
const float RAIL_PLANK_WIDTH = 0.4;
const float RAIL_PLANK_DEPTH = TRACK_WIDTH * 1.5;
const int NR_OF_RAIL_PLANKS = GROUND_LENGTH / RAIL_PLANK_WIDTH / 2;

const float WALL_HEIGHT = 4;
const float WALL_THICKNESS = 2;

const float WHEEL_ROT_SPEED = 0.01;
const float LOCOMOTIVE_SPEED = 2 * M_PI * WHEEL_RADIUS / (2 * M_PI / WHEEL_ROT_SPEED);

const float GROUND_Z = -WHEEL_RADIUS - RAILS_HEIGHT - RAIL_PLANK_HEIGHT;

class Locomotive
{
private:
	RenderedObject* wheels[NR_OF_WHEELS];
	RenderedObject* bar[2];
	RenderedObject* chassis;
	RenderedObject* rails[2];
	RenderedObject* rail_planks[2];
	RenderedObject* ground[2];
	RenderedObject* walls[2];
	RenderedObject* sky;

	std::vector<Texture*> textures;

	Shader* sky_shader;
public:
	Locomotive()
	{
		loadTextures();

		createWheels(0);

		chassis = new RenderedObject(connectedRectangles(glm::vec2(-1 * WHEELBASE / 2 - WHEEL_RADIUS, 0),
		                                                 glm::vec2(WHEELBASE / 2 + WHEEL_RADIUS, 0),
		                                                 0.5, TRACK_WIDTH - WHEEL_DEPTH, true), textures[1]);

		createBars(0);

		createRails(2);

		createRailPlanks(3);

		createGround(4);

		createWalls(5);

		sky = new RenderedObject(sphere(40, GROUND_LENGTH / 2, true), textures[6]);
		sky->moveBy(0, GROUND_Z, 0);
		sky->rotateBy(0, M_PI, 0);

		sky_shader = new Shader("sky_shader");
	}

	void loadTextures()
	{
		textures.push_back(new Texture("red_painted_metal.png"));
		textures.push_back(new Texture("green_planks.jpg"));
		textures.push_back(new Texture("steel.jpg"));
		textures.push_back(new Texture("wood.png"));
		textures.push_back(new Texture("grass.jpg"));
		textures.push_back(new Texture("bricks.jpg"));
		textures.push_back(new Texture("sky.jpg"));
	}

	void createWheels(int texture_id)
	{
		for (unsigned int i = 0; i < NR_OF_WHEELS; ++i)
		{
			Vertices temp = wheel(WHEEL_VERTICES, WHEEL_DEPTH, WHEEL_THICKNESS, NR_OF_WHEEL_SPOKES, WHEEL_RADIUS);

			if (i < NR_OF_WHEELS / 2)
			{
				wheels[i] = new RenderedObject(temp, textures[texture_id]);
				wheels[i]->moveBy(WHEELBASE / 2 - i % (NR_OF_WHEELS / 2) * WHEELBASE / ((NR_OF_WHEELS) / 2 - 1), 0,
				                  -1 * TRACK_WIDTH / 2);
			}
			else
			{
				temp.turnBack();
				wheels[i] = new RenderedObject(temp, textures[texture_id]);
				wheels[i]->moveBy(WHEELBASE / 2 - i % (NR_OF_WHEELS / 2) * WHEELBASE / ((NR_OF_WHEELS) / 2 - 1), 0,
				                  TRACK_WIDTH / 2);
			}
		}
	}

	void createBars(int texture_id)
	{
		Vertices connection_verts[NR_OF_WHEELS];
		Vertices bar_verts[2];

		for(int i = 0; i < 2; ++i)
			bar_verts[i] = connectedRectangles(glm::vec2(-1 * WHEELBASE / 2, 0), glm::vec2(WHEELBASE / 2, 0), BAR_WIDTH, BAR_DEPTH, true);

		int side_z = 1;
		for (int i = 0; i < NR_OF_WHEELS; ++i)
		{
			connection_verts[i] = connectedPolygons(WHEEL_VERTICES, WHEEL_DEPTH + BAR_DEPTH * 1.2, BAR_WIDTH);

			if (i >= NR_OF_WHEELS / 2)
				side_z = -1;

			connection_verts[i].moveBy(WHEELBASE / 2 - i % (NR_OF_WHEELS / 2) * WHEELBASE / ((NR_OF_WHEELS) / 2 - 1), 0, side_z * (WHEEL_DEPTH / 2 - BAR_DEPTH * 0.1));
			bar_verts[(side_z - 1)/(-2)].add(connection_verts[i]);
		}

		for (int i = 0; i < 2; ++i)
			bar[i] = new RenderedObject(bar_verts[i], textures[texture_id]);

		bar[0]->moveBy(0, BAR_POS_RADIUS, -1 * (TRACK_WIDTH + WHEEL_DEPTH + BAR_DEPTH) / 2);
		bar[1]->moveBy(0, BAR_POS_RADIUS, (TRACK_WIDTH + WHEEL_DEPTH + BAR_DEPTH) / 2);
	}

	void createRails(int texture_id)
	{
		int side = 0;

		Vertices rails_vert[4];

		for (int i = 0; i < 4; ++i)
		{
			if (i < 2)
				side = -1;
			else
				side = 1;

			rails_vert[i] = connectedRectangles(
				glm::vec3(-GROUND_LENGTH / 2, GROUND_Z + RAIL_PLANK_HEIGHT + RAILS_HEIGHT / 2, side * TRACK_WIDTH / 2 - WHEEL_DEPTH/4),
				glm::vec3(GROUND_LENGTH / 2, GROUND_Z + RAIL_PLANK_HEIGHT + RAILS_HEIGHT / 2, side * TRACK_WIDTH / 2 - WHEEL_DEPTH/4),
				RAILS_HEIGHT, WHEEL_DEPTH / 2);

			rails_vert[i].add(connectedRectangles(
				glm::vec3(-GROUND_LENGTH / 2, GROUND_Z + RAIL_PLANK_HEIGHT + RAILS_HEIGHT / 2 + WHEEL_THICKNESS / 4, side * TRACK_WIDTH / 2 + WHEEL_DEPTH/4),
				glm::vec3(GROUND_LENGTH / 2, GROUND_Z + RAIL_PLANK_HEIGHT + RAILS_HEIGHT / 2 + WHEEL_THICKNESS / 4, side * TRACK_WIDTH / 2 + WHEEL_DEPTH/4),
				RAILS_HEIGHT + WHEEL_THICKNESS / 2, WHEEL_DEPTH / 2));

			if (side == -1)
			{
				rails_vert[i].turnBack();
				rails_vert[i].moveBy(0, 0, side * TRACK_WIDTH);
			}

			if (i % 2 == 0)
				rails_vert[i].moveBy(-GROUND_LENGTH, 0, 0);

		}

		rails_vert[0].add(rails_vert[2]);
		rails_vert[1].add(rails_vert[3]);
		rails[0] = new RenderedObject(rails_vert[0], textures[texture_id]);
		rails[1] = new RenderedObject(rails_vert[1], textures[texture_id]);
	}

	void createRailPlanks(int texture_id)
	{
		Vertices planks_vert;
		Vertices first_plank = connectedRectangles(glm::vec2(-GROUND_LENGTH / 2, GROUND_Z + RAIL_PLANK_HEIGHT / 2),
		                                           glm::vec2(-GROUND_LENGTH / 2 + RAIL_PLANK_WIDTH, GROUND_Z + RAIL_PLANK_HEIGHT / 2),
		                                           RAIL_PLANK_HEIGHT, RAIL_PLANK_DEPTH, true);

		Vertices temp;
		temp = first_plank;

		for (int i = 0; i < NR_OF_RAIL_PLANKS; ++i)
		{
			planks_vert.add(temp, false);

			temp.moveBy(RAIL_PLANK_WIDTH * 2, 0, 0);
		}
		planks_vert.calcNormals();

		rail_planks[1] = new RenderedObject(planks_vert, textures[texture_id]);

		planks_vert.moveBy(-GROUND_LENGTH, 0, 0);

		rail_planks[0] = new RenderedObject(planks_vert, textures[texture_id]);
	}

	void createGround(int texture_id)
	{
		for (int i = 0; i < 2; ++i)
		{
			ground[i] = new RenderedObject(rectangle(glm::vec3(-GROUND_LENGTH / 2, 0, -GROUND_LENGTH / 2),
			                                         glm::vec3(-GROUND_LENGTH / 2, 0, GROUND_LENGTH / 2),
			                                         glm::vec3(GROUND_LENGTH / 2, 0, -GROUND_LENGTH / 2),
			                                         glm::vec3(GROUND_LENGTH / 2, 0, GROUND_LENGTH / 2)), textures[texture_id]);

			if (i == 0)
				ground[i]->moveBy(-GROUND_LENGTH, 0, 0);

			ground[i]->moveBy(0, GROUND_Z, 0);
		}
	}

	void createWalls(int texture_id)
	{
		int side = 0;

		Vertices temp[4];

		for (int i = 0; i < 4; ++i)
		{
			if (i < 2)
				side = -1;
			else
				side = 1;

			if (i % 2 == 0)
				temp[i] = connectedRectangles(
					glm::vec3(-3 * GROUND_LENGTH / 2, GROUND_Z + WALL_HEIGHT / 2, side * GROUND_WIDTH / 2),
					glm::vec3(-GROUND_LENGTH / 2, GROUND_Z + WALL_HEIGHT / 2, side * GROUND_WIDTH / 2),
					WALL_HEIGHT,
					WALL_THICKNESS);
			else
				temp[i] = connectedRectangles(glm::vec3(-GROUND_LENGTH / 2, GROUND_Z + WALL_HEIGHT / 2, side * GROUND_WIDTH / 2),
				                              glm::vec3(GROUND_LENGTH / 2, GROUND_Z + WALL_HEIGHT / 2, side * GROUND_WIDTH / 2),
				                              WALL_HEIGHT,
				                              WALL_THICKNESS);
		}

		temp[0].add(temp[2]);
		temp[1].add(temp[3]);

		walls[0] = new RenderedObject(temp[0], textures[texture_id]);
		walls[1] = new RenderedObject(temp[1], textures[texture_id]);
	}

	void createTrees(int texture_id)
	{
		const int NR_OF_TREES = 2;
		const float TREE_RADIUS = 2;
		const float TREE_HEIGHT = 7;

		Vertices tree_vert;
		for(int i = 0; i < NR_OF_TREES; ++i)
		{
			Vertices temp;

			temp = sphere(40, TREE_RADIUS);

			int side_z = 1;
			if (i < NR_OF_TREES / 2)
				side_z = -1;

			temp.moveBy(0, TREE_HEIGHT - 2 * TREE_RADIUS, side_z * GROUND_WIDTH / 2);

			tree_vert.add(temp, false);
		}
		tree_vert.calcNormals();

		//trees = new RenderedObject(tree_vert, filename);
	}

	void moveForward()
	{
		for (int i = 0; i < 2; ++i)
		{
			ground[i]->moveBy(LOCOMOTIVE_SPEED, 0, 0);
			walls[i]->moveBy(LOCOMOTIVE_SPEED, 0, 0);
			rails[i]->moveBy(LOCOMOTIVE_SPEED, 0, 0);
			rail_planks[i]->moveBy(LOCOMOTIVE_SPEED, 0, 0);
		}

		if (ground[1]->getPosition().x >= GROUND_LENGTH)
		{
			float dist = ground[1]->getPosition().x;

			std::swap(ground[0], ground[1]);
			ground[0]->moveBy(-2 * dist, 0, 0);

			std::swap(walls[0], walls[1]);
			walls[0]->moveBy(-2 * dist, 0, 0);

			std::swap(rails[0], rails[1]);
			rails[0]->moveBy(-2 * dist, 0, 0);

			std::swap(rail_planks[0], rail_planks[1]);
			rail_planks[0]->moveBy(-2 * dist, 0, 0);
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

		chassis->draw(texture_unit, shader, camera);

		for (int i = 0; i < 2; ++i)
		{
			bar[i]->draw(texture_unit, shader, camera);

			bar[i]->moveInCircleByAngle(WHEEL_ROT_SPEED, BAR_POS_RADIUS);
		}

		for (int i = 0; i < 2; ++i)
			ground[i]->draw(texture_unit, shader, camera);

		moveForward();

		for (int i = 0; i < 2; ++i)
			walls[i]->draw(texture_unit, shader, camera);

		sky->draw(texture_unit, *sky_shader, camera);

		for (int i = 0; i < 2; ++i)
		{
			rails[i]->draw(texture_unit, shader, camera);
		}

		for (int i = 0; i < 2; ++i)
		{
			rail_planks[i]->draw(texture_unit, shader, camera);
		}
	}
};

#endif
