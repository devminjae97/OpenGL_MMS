#pragma once
#include "actor.h"

class MainCharacter : public Actor {
private:
	// Input
	bool is_key_right_pressed = false;
	bool is_key_left_pressed = false;
	bool is_key_space_pressed = false;

	float power_accel_axis_horizontal = 8.f;	// 1->1sec, 2->0.5sec
	float power_accel_axis_horizontal_on_air = .5f;	//
	float power_stop_axis_horizontal = 6.f;

	// Variable for movement

	bool is_jumping = false;
	//glm::vec3 vec_walk_unit = glm::vec3(0.00125f, 0, 0);	// why 0.00125?	-> float 단일로 바꾸기
	glm::vec3 vec_walk_unit = glm::vec3(1.28, 0, 0);	// why 1.28?	-> float 단일로 바꾸기

	// └> Status
	float mainCharacter_speed = 160;	// => 160% 
	float mainCharacter_jumpPower = 123;	// => 123%


	// GroundCheck
	Collision* collision_groundchecker;
	float offset_y_collision_groundchecker = -36;


public:
	MainCharacter();
	~MainCharacter();

	void Activate(double dt);

	//-------------
	// <Key Input>

	void GetKeyInput(double dt);

	void Walk(double dt);
	void Jump();
	void Attack();

	void Skill_DoubleJump();



	void CheckCollision();
	void CollisionResolution(Collision* other);


	//test
	void SwitchAnimation();	// make it virtual in parent?

	void GroundCheck();



	//------------
	// test physics - do i need to seperate it to another file?

	glm::vec3 velocity = glm::vec3(0.f);	//for jump?
	glm::vec3 velocity_walk = glm::vec3(0.f);
	float axis_horizontal = 0;	//for walk?

	float terminal_velocity = -675.f; //  22.5px/frame * 30fps
	float gravity = 2000.f;

	void ApplyGravity(double dt);

	// Tmp
	void FallResolution();







};