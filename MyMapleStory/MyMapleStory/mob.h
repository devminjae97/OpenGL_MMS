#pragma once

#include "actor.h"

class Mob : Actor {

private:

	float power_accel_axis_horizontal = 16.f;	// 1->1sec, 2->0.5sec
	float power_accel_axis_horizontal_on_air = .5f;	//
	float power_stop_axis_horizontal = 6.f;

	// Variable for movement
	//glm::vec3 vec_walk_unit = glm::vec3(0.00125f, 0, 0);	// why 0.00125?	-> float 단일로 바꾸기
	glm::vec3 vec_walk_unit = glm::vec3(1.28, 0, 0);	// why 1.28?	-> float 단일로 바꾸기

	// └> Status
	float speed = 100; 
	float jumpPower = 100;


	//-------------------------------
	// related to jump & gravity
	bool is_jump_enabled = false;

	bool is_jumping = false;
	// GroundCheck
	Collision* collision_groundchecker;
	float offset_y_collision_groundchecker = -36;



	//--------------------
	// motion
	int num_motions = 2;	// idle, walk
	int current_motion = 1;
	float time_to_motion_change = 0;
	float time_to_jump = 0;


public:
	Mob(int w, int h, std::string name, bool is_jump_enabled);
	~Mob();
	void Update(double dt);
	void EnableJump();

	void SwitchMotion(double dt); 
	void Walk(double dt);
	void Jump();
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