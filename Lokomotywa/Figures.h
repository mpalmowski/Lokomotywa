#ifndef WHEEL_HPP
#define WHEEL_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vertices.hpp"

Vertices regularPolygon(unsigned int nr_of_vertices, float z, float radius = 1);

Vertices ringPolygon(unsigned int nr_of_vertices, float z, float inner_radius, float radius = 1);

Vertices connectedRings(unsigned int nr_of_vertices, float thickness, float inner_radius, float radius = 1);

Vertices connectedPolygons(unsigned int nr_of_vertices, float thickness, float radius = 1);

#endif