#pragma once

#include "component.h"

class Collider;
class RigidBody : public Component {

	// basic
private:
	bool isUpdatable = true;

public:
	RigidBody(std::string name);
	~RigidBody();

	virtual void Awake() override;
	virtual void Update(double dt) override;


	// values
private:
	float mass = 1;

	float velocity_x = 0;
	float velocity_y = 0;

	float terminalVelocity_y = -675.f; //  22.5px/frame * 30fps
	float gravity = 2000.f;

	float drag = 6.0f;

public:
	void AddForce(float ax, float ay);
	void DoGravity(double dt);
	void Stop();
	void ResolveCollision(Collider* other);
};