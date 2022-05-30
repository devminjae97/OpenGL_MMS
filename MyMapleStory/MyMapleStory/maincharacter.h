#pragma once
#include "actor.h"

class MainCharacter : public Actor {
private:

public:
	MainCharacter();



	// Input
	bool is_key_right_pressed = false;
	bool is_key_left_pressed = false;
	bool is_key_spacebar_pressed = false;

	float axis_horizontal_right = 0;
	float axis_horizontal_left = 0;
	float power_accel_axis_horizontal = 8.f;	// 1->1sec, 2->0.5sec
	float power_stop_axis_horizontal = 8.f;

	// Variable for movement

	bool is_facing_right = false;
	bool is_jumping = false;
	glm::vec3 vec_walk_unit = glm::vec3(0.0025f, 0, 0);
	glm::mat4 mat_translate = glm::mat4(1.0f);
	glm::mat4 mat_scale = glm::mat4(1.0f);

	// ¦¦> Status
	float mainCharacter_speed = 160;
	float mainCharacter_jumpPower;




	void SetColliderTransform(glm::mat4 mt, int w, int h);

	void Activate(double dt);

	//-------------
	// <Key Input>

	void GetKeyInput(double dt);

	void Walk(double dt);
	void FaceRight(bool b);
	void Jump();
	void Attack();

};