#ifndef WHEEL_HPP
#define WHEEL_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "Vertices.hpp"

Vertices regularPolygon(unsigned int nr_of_vertices, float z, float radius = 1);

Vertices ringPolygon(unsigned int nr_of_vertices, float z, float inner_radius, float radius = 1);

Vertices connectedRings(unsigned int nr_of_vertices, float depth, float inner_radius, float radius = 1);

Vertices connectedPolygons(unsigned int nr_of_vertices, float depth, float radius = 1);

Vertices rectangle(glm::vec3 bottom_left, glm::vec3 bottom_right, glm::vec3 top_left, glm::vec3 top_right);

Vertices connectedRectangles(glm::vec2 start, glm::vec2 finish, float width, float depth, bool with_top_and_bottom = false);

Vertices wheel(unsigned int nr_of_vertices, float depth, float thickness, float nr_of_spokes);

#endif