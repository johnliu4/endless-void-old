#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

class PhysicsEngine {
private:
	static PhysicsEngine* instance;
public:
	static PhysicsEngine* get_instance();
	PhysicsEngine();
	~PhysicsEngine();
};

#endif