#include "math.h"

/* Checks distance between centers of box on each axis. */
bool intersects(const AABB& aabb1, const AABB& aabb2) {
	if (glm::abs(aabb2.pos.x - aabb1.pos.x)
		< aabb1.width / 2.0f + aabb2.width / 2.0f) {
		if (glm::abs(aabb2.pos.y - aabb1.pos.y)
			< aabb1.height / 2.0f + aabb2.height / 2.0f) {
			if (glm::abs(aabb2.pos.z - aabb1.pos.z)
				< aabb1.length / 2.0f + aabb2.length/ 2.0f) {
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