#pragma once
#include "actor.h"

class MainCharacter : public Actor {
private:
	// Input
	bool is_key_right_pressed = false;
	bool is_key_left_pressed = false;
	bool is_key_spacebar_pressed = false;

	float axis_horizontal_right = 0;
	float axis_horizontal_left = 0;
	float power_accel_axis_horizontal = 8.f;	// 1->1sec, 2->0.5sec
	float power_stop_axis_horizontal = 8.f;

	// Variable for movement

	bool is_jumping = false;
	glm::vec3 vec_walk_unit = glm::vec3(0.00125f, 0, 0);	// why 0.00125?	-> float 단일로 바꾸기

	// └> Status
	float mainCharacter_speed = 160;	// => 160% 
	float mainCharacter_jumpPower = 123;	// => 123%


	// prev frame position
	float prev_x = 0;
	float prev_y = 0;


public:
	MainCharacter();


	void Activate(double dt);

	//-------------
	// <Key Input>

	void GetKeyInput(double dt);

	void Walk(double dt);
	void Jump();
	void Attack();

	void SavePrevPosition();

	//------------
	// test
	void CheckCollision();
	void CollisionResolution(Collision* c);
};