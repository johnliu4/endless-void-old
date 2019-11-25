#include <limits>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "math.h"

/* Checks distance between centers of box on each axis. */
bool intersects(const AABB& aabb1, const AABB& aabb2) {
	if (glm::abs(aabb2.pos.x - aabb1.pos.x)
		< aabb1.width / 2.0f + aabb2.width / 2.0f - EPSILON) {
		if (glm::abs(aabb2.pos.y - aabb1.pos.y)
			< aabb1.height / 2.0f + aabb2.height / 2.0f - EPSILON) {
			if (glm::abs(aabb2.pos.z - aabb1.pos.z)
				< aabb1.length / 2.0f + aabb2.length / 2.0f - EPSILON) {
				

				//std::cout << "z diff: " << (glm::abs(aabb2.pos.z - aabb1.pos.z)) << std::endl;
				//std::cout << "length diff: " << (aabb1.length / 2.0f + aabb2.length / 2.0f - EPSILON) << std::endl;

				return true;
			}
		}
	}

	return false;
}

bool intersects(const AABB& aabb, const Plane& plane) {
	// get vertices of aabb
	GLfloat hw = aabb.width / 2.0f;
	GLfloat hh = aabb.height / 2.0f;
	GLfloat hl = aabb.length / 2.0f;
	glm::vec3 vertices[8] = {
		glm::vec3(-hw, -hh, -hl),
		glm::vec3(-hw, -hh, hl),
		glm::vec3(hw, -hh, hl),
		glm::vec3(hw, -hh, -hl),
		glm::vec3(-hw, hh, -hl),
		glm::vec3(-hw, hh, hl),
		glm::vec3(hw, hh, hl),
		glm::vec3(hw, hh, -hl),
	};
	// translate aabb vertices such that they are relative to plane point
	// this allows you to determine which half of the plane a vertex is on
	// sign of the dot product with the plane norm determines what half the point is on
	// all that is needed to do is to check that all points are on the same half
	glm::vec3 v = vertices[0] - plane.point;
	bool first_point_positive = glm::dot(v, plane.norm) > 0.0f;
	for (int i = 1; i < 8; i++) {
		v = vertices[i] - plane.point;
		bool positive = glm::dot(v, plane.norm) >= 0.0f;
		// if any subsequent point does not also fall on the same half
		// then the aabb is colliding with the plane
		if (positive != first_point_positive) {
			return false;
		}
	}

	return true;

}

bool intersects(const Sphere& sphere1, const Sphere& sphere2) {
	glm::vec3 diff = sphere2.pos - sphere1.pos;
	// compare squared distances between sphere centers with their combined radius
	// distances are squared to avoid using an expensive square root call to find true distance
	return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z
		<= sphere1.radius * sphere1.radius + sphere2.radius * sphere2.radius;
}

intersect_details compute_intersect(const AABB& aabb1, const AABB& aabb2, const glm::vec3 disp) {
	// compute the minkowski difference AABB2 - AABB1
	glm::vec3 half1(aabb1.width / 2.0f, aabb1.height / 2.0f, aabb1.length / 2.0f);
	glm::vec3 half2(aabb2.width / 2.0f, aabb2.height / 2.0f, aabb2.length / 2.0f);
	glm::vec3 pos_diff = aabb2.pos - aabb1.pos;

	// the minkowski difference of two AABBs always yields another AABB
	// therefore we only need to find the min and max vertices
	glm::vec3 mink_min(
		pos_diff.x - half2.x - half1.x, pos_diff.y - half2.y - half1.y, pos_diff.z - half2.z - half1.z);
	glm::vec3 mink_max(
		pos_diff.x + half2.x + half1.x, pos_diff.y + half2.y + half1.y, pos_diff.z + half2.z + half1.z);

	// the minkowski AABB represents a space where if you extend a ray from the origin
	// and it collides with the minkowski AABB, then the same ray applied to the displacement
	// of the first shape will collide with the second shape
	// so first check if the minkowski difference contains the origin
	// if it does, then the AABBs are already intersecting

	// epsilon is used here to give leeway for AABBs that are just touching
	if (
		mink_min.x <= -EPSILON && mink_max.x >= EPSILON &&
		mink_min.y <= -EPSILON && mink_max.y >= EPSILON &&
		mink_min.z <= -EPSILON && mink_max.z >= EPSILON
	) {
		return { false, 0.0f, glm::vec3(0.0f) };
	}

	// check if the displacement vector collides with each of the 6 minkowski AABB faces from the origin
	// and find the closest intersection if it exists
	bool intersects = false;
	GLfloat min_intersection = 1.0f;
	glm::vec3 intersect_normal(0.0f);

	// left face
	if (disp.x > 0.0f && mink_min.x >= -EPSILON) {
		GLfloat scalar_intersection = mink_min.x / disp.x;
		glm::vec3 intersection_point = disp * scalar_intersection;
		// check if intersection point is inside the rectangular face on yz plane
		if (intersection_point.y >= mink_min.y && intersection_point.y <= mink_max.y
			&& intersection_point.z >= mink_min.z && intersection_point.z <= mink_max.z) {
			if (scalar_intersection < min_intersection) {
				min_intersection = scalar_intersection;
				intersect_normal = glm::vec3(1.0f, 0.0f, 0.0f);
				intersects = true;
			}
		}
	}

	// right face
	if (disp.x < 0.0f && mink_max.x <= EPSILON) {
		GLfloat scalar_intersection = glm::abs(mink_max.x / disp.x);
		glm::vec3 intersection_point = disp * scalar_intersection;
		// check if intersection point is inside the rectangular face on yz plane
		if (intersection_point.y >= mink_min.y && intersection_point.y <= mink_max.y
			&& intersection_point.z >= mink_min.z && intersection_point.z <= mink_max.z) {
			if (scalar_intersection < min_intersection) {
				min_intersection = scalar_intersection;
				intersect_normal = glm::vec3(-1.0f, 0.0f, 0.0f);
				intersects = true;
			}
		}
	}

	// bottom face
	if (disp.y > 0.0f && mink_min.y >= -EPSILON) {
		GLfloat scalar_intersection = glm::abs(mink_min.y / disp.y);
		glm::vec3 intersection_point = disp * scalar_intersection;
		// check if intersection point is inside the rectangular face on xz plane
		if (intersection_point.x >= mink_min.x && intersection_point.x <= mink_max.x
			&& intersection_point.z >= mink_min.z && intersection_point.z <= mink_max.z) {
			if (scalar_intersection < min_intersection) {
				min_intersection = scalar_intersection;
				intersect_normal = glm::vec3(0.0f, 1.0f, 0.0f);
				intersects = true;
			}
		}
	}

	// top face
	if (disp.y < 0.0f && mink_max.y <= EPSILON) {
		GLfloat scalar_intersection = mink_max.y / disp.y;
		glm::vec3 intersection_point = disp * scalar_intersection;
		// check if intersection point is inside the rectangular face on xz plane
		if (intersection_point.x >= mink_min.x && intersection_point.x <= mink_max.x
			&& intersection_point.z >= mink_min.z && intersection_point.z <= mink_max.z) {
			if (scalar_intersection < min_intersection) {
				min_intersection = scalar_intersection;
				intersect_normal = glm::vec3(0.0f, -1.0f, 0.0f);
				intersects = true;
			}
		}
	}

	// back face
	if (disp.z > 0.0f && mink_min.z >= -EPSILON) {
		GLfloat scalar_intersection = mink_min.z / disp.z;
		glm::vec3 intersection_point = disp * scalar_intersection;
		// check if intersection point is inside the rectangular face on xy plane
		if (intersection_point.x >= mink_min.x && intersection_point.x <= mink_max.x
			&& intersection_point.y >= mink_min.y && intersection_point.y <= mink_max.y) {
			if (scalar_intersection < min_intersection) {
				min_intersection = scalar_intersection;
				intersect_normal = glm::vec3(0.0f, 0.0f, 1.0f);
				intersects = true;
			}
		}
	}

	// front face
	if (disp.z < 0.0f && mink_max.z <= EPSILON) {
		GLfloat scalar_intersection = glm::abs(mink_max.z / disp.z);
		glm::vec3 intersection_point = disp * scalar_intersection;
		// check if intersection point is inside the rectangular face on xy plane
		if (intersection_point.x >= mink_min.x && intersection_point.x <= mink_max.x
			&& intersection_point.y >= mink_min.y && intersection_point.y <= mink_max.y) {
			if (scalar_intersection < min_intersection) {
				min_intersection = scalar_intersection;
				intersect_normal = glm::vec3(0.0f, 0.0f, -1.0f);
				intersects = true;
			}
		}
	}
	
	return { intersects, min_intersection, intersect_normal };
}

AABB get_minimum_aabb(const AABB& aabb1, const AABB& aabb2) {
	glm::vec3 half1(aabb1.width / 2.0f, aabb1.height / 2.0f, aabb1.length / 2.0f);
	glm::vec3 half2(aabb2.width / 2.0f, aabb2.height / 2.0f, aabb2.length / 2.0f);
	glm::vec3 min(
		glm::min(aabb1.pos.x - half1.x, aabb2.pos.x - half2.x),
		glm::min(aabb1.pos.y - half1.y, aabb2.pos.y - half2.y),
		glm::min(aabb1.pos.z - half1.z, aabb2.pos.z - half2.z));
	glm::vec3 max(
		glm::max(aabb1.pos.x + half1.x, aabb2.pos.x + half2.x),
		glm::max(aabb1.pos.y + half1.y, aabb2.pos.y + half2.y),
		glm::max(aabb1.pos.z + half1.z, aabb2.pos.z + half2.z));
	return AABB(
		glm::vec3((max.x + min.x) / 2.0f, (max.y + min.y) / 2.0f, (max.z + min.z) / 2.0f),
		max.x - min.x, max.y - min.y, max.z - min.z);
}