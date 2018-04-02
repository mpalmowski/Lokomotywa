#ifndef WHEEL_HPP
#define WHEEL_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vertices.hpp"
#include <iostream>;

Vertices regularPolygon(unsigned int nr_of_vertices, float z, float radius = 1);

Vertices ringPolygon(unsigned int nr_of_vertices, float z, float inner_radius, float radius = 1);

Vertices connectedRings(unsigned int nr_of_vertices, float thickness, float inner_radius, float radius = 1);

Vertices connectedPolygons(unsigned int nr_of_vertices, float thickness, float radius = 1);

Vertices square(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_left, glm::vec3 top_right);

Vertices plank(glm::vec2 start, glm::vec2 finish, float width, float depth);

Vertices wheel(unsigned int nr_of_vertices, float thickness, float nr_of_spokes);

#endif