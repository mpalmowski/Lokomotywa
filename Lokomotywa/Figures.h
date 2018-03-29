#ifndef WHEEL_HPP
#define WHEEL_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vertices.hpp"

Vertices *createRegularPolygon(unsigned int nr_of_vertices, float z, float radius = 1);

Vertices *createRingPolygon(unsigned int nr_of_vertices, float z, float inner_radius, float radius = 1);

#endif