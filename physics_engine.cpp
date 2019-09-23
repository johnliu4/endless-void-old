#include "physics_engine.h"

PhysicsEngine* PhysicsEngine::instance = nullptr;
PhysicsEngine* PhysicsEngine::get_instance() {
	if (instance == nullptr) {
		instance = new PhysicsEngine();
	}

	return instance;
}

PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {
	delete instance;
}