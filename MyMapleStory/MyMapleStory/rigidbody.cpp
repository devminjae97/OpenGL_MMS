#include "rigidbody.h"
#include "entity.h"
#include "collider.h"

RigidBody::RigidBody(std::string name) : Component(name) {

}

RigidBody::~RigidBody() {

}

void RigidBody::Awake() {

}

void RigidBody::Update(double dt) {
	// calculate velocity
	if (isUpdatable) {
		DoGravity(dt);
		owner->AddPosition(velocity_x * dt, velocity_y * dt);
	}
}

void RigidBody::AddForce(float ax, float ay) {
	velocity_x += ax;
	velocity_y += ay;
}

void RigidBody::DoGravity(double dt) {
	if (velocity_y > terminalVelocity_y)
		velocity_y -= gravity * (float)dt;
}

void RigidBody::Stop() {
	velocity_x = 0;
	velocity_y = 0;
}

void RigidBody::ResolveCollision(Collider* other) {
    Collider* coll = owner->GetComponent<Collider>("collider");

    glm::vec2 pos_this = coll->GetPosition();
    glm::vec2 pos_other = other->GetPosition();
    glm::vec2 scale_this = coll->GetScale();
    glm::vec2 scale_other = other->GetScale();


    int horizontal = pos_this.x > other->GetPosition().x ? 1 : -1;
    int vertical = pos_this.y > other->GetPosition().y ? 1 : -1;

    float overlapped_amount_x = abs((pos_this.x - horizontal * scale_this.x / 2) - (pos_other.x + horizontal * scale_other.x / 2));
    float overlapped_amount_y = abs((pos_this.y - vertical * scale_this.y / 2) - (pos_other.y + vertical * scale_other.y / 2));

    // vertical
    if (overlapped_amount_x > overlapped_amount_y) {
        owner->SetPosition(owner->transform.position.x, pos_other.y + vertical * (scale_other.y / 2 + scale_this.y / 2));

        velocity_y = 0;
    }
    // horizontal
    else {
        owner->SetPosition(pos_other.x + horizontal * (scale_other.x / 2 + scale_this.x / 2), owner->transform.position.y);
        //axis_horizontal = 0;

        velocity_x = 0;   // then stop
    }
}