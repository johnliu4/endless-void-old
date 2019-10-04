#ifndef MATH_H
#define MATH_H

#include "aabb.h"
#include "plane.h"
#include "sphere.h"

/*
 * Math and physics for World Engine.
 * A set of basic collision detection and resolution
 * algorithms are here for use in handling physics.
 */

bool intersects(const AABB& aabb1, const AABB& aabb2);
bool intersects(const AABB& aabb, const Plane& plane);
bool intersects(const Sphere& sphere1, const Sphere& sphere2);

#endif