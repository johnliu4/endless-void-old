#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/string_cast.hpp>

#include "physics_engine.h"
#include "math.h"

using glm::vec3;

PhysicsEngine::PhysicsEngine() {
	gravity = 9.81f;
	dynamic_aabb = nullptr;
}

void PhysicsEngine::set_dynamic_aabb(DynamicAABB* aabb) {
	dynamic_aabb = aabb;
}

void PhysicsEngine::add_static_aabb(AABB* aabb) {
	static_aabbs.push_back(aabb);
}

void PhysicsEngine::remove_static_aabb(AABB* aabb) {
	static_aabbs.remove(aabb);
}


/* Performs one update in the physics world. */
void PhysicsEngine::update() {
	if (dynamic_aabb != nullptr) {
		//std::cout << "********************" << std::endl;
		//std::cout << "vel.y bef: " << dynamic_aabb->vel.y << std::endl;
		dynamic_aabb->vel.y -= gravity * TICK_TIME;
		//std::cout << "vel.y aft: " << dynamic_aabb->vel.y << std::endl;
		GLfloat prev_vel_y = dynamic_aabb->vel.y;
		AABB aabb = *dynamic_aabb;
		//std::cout << "aabb.vel: " << glm::to_string(aabb.vel) << std::endl;
		glm::vec3 current_disp = aabb.vel * TICK_TIME;

		while (glm::length(current_disp) >= EPSILON) {
			//std::cout << "**********" << std::endl;
			// find the maximum distance that the AABB can move without intersecting with anything
			intersect_details min_intersect = { false, 1.0f };
			AABB before_aabb = aabb;
			aabb.pos += current_disp;
			//std::cout << "current_disp: " << glm::to_string(current_disp) << std::endl;

			AABB min_enclosing = get_minimum_aabb(before_aabb, aabb);

			for (auto it_static = static_aabbs.begin(); it_static != static_aabbs.end(); it_static++) {
				if (intersects(min_enclosing, **it_static)) {
					intersect_details details = compute_intersect(before_aabb, **it_static, current_disp);

					//std::cout << (**it_static).to_string() << std::endl;

					if (!min_intersect.intersects) {
						min_intersect = details;
					} else if (details.scalar < min_intersect.scalar) {
						min_intersect.scalar = details.scalar;
						min_intersect.face_normal = details.face_normal;
					}
				}
			}

			if (min_intersect.intersects) {
				//std::cout << "***" << std::endl;
				//std::cout << glm::to_string(aabb.pos) << std::endl;

				// move aabb back to the position of intersection
				aabb.pos -= (1.0f - min_intersect.scalar) * current_disp;
				//std::cout << glm::to_string(aabb.pos) << std::endl;
				//std::cout << glm::to_string(current_disp) << std::endl;
				//std::cout << min_intersect.intersects << ", " << min_intersect.scalar << ", " << glm::to_string(min_intersect.face_normal) << std::endl;

				//std::cout << "current_disp bef: " << glm::to_string(current_disp) << std::endl;
				current_disp *= 1.0f - min_intersect.scalar;
				glm::vec3 normal_proj = glm::proj(current_disp, min_intersect.face_normal);
				current_disp -= normal_proj;
				//std::cout << "current_disp aft: " << glm::to_string(current_disp) << std::endl;
				//std::cout << "aabb.vel bef: " << glm::to_string(aabb.vel) << std::endl;
				aabb.vel = current_disp / TICK_TIME;
				// apply friction due to gravity
				glm::vec3 xz_vel(aabb.vel.x, 0.0f, aabb.vel.z);
				if (glm::length(xz_vel) > EPSILON && glm::abs(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), min_intersect.face_normal)) >= 1.0f - EPSILON) {
					glm::vec3 frictional_slow = glm::normalize(xz_vel) * dynamic_aabb->base_friction * gravity * TICK_TIME;
					if (glm::length(frictional_slow) > glm::length(xz_vel)) {
						aabb.vel.x = 0.0f;
						aabb.vel.z = 0.0f;
					} else {
						aabb.vel -= frictional_slow;
					}
				}
				//std::cout << "aabb.vel aft: " << glm::to_string(aabb.vel) << std::endl;

				//std::cout << glm::to_string(current_disp) << std::endl;
				//std::cout << "***" << std::endl;
			} else {
				break;
			}
		}
		
		// if the box was previously moving downwards (or was not moving)
		// and is now not moving in the y-axis then it must be grounded
		aabb.grounded = prev_vel_y <= 0.0f && glm::abs(aabb.vel.y) < EPSILON;
		*dynamic_aabb = aabb;
		//std::cout << "dyn.vel: " << glm::to_string(dynamic_aabb->vel) << std::endl;
	}
}