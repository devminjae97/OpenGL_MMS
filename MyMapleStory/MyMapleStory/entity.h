#pragma once

#include "global.h"
#include "collision.h"
#include "shader.h"
#include "animator.h"


class Entity {

public:

	struct Transform {
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		unsigned width = 128;
		unsigned height = 128;
	}transform;

	glm::mat4 mat_model = glm::mat4(1.f);

	// Shader
	Shader* shader;



	// Collider
	bool isColliderOn;
	Collision* collision;


	// GL variables
	unsigned  int VBO, VAO, EBO;

	float vertices[32] = {
		.25f, .5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,     // RT
		.25f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,     // RB
		-.25f, -.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // LB
		-.25f, .5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // LT
	};  // range >> position: -1 ~ 1/ colour: 0 ~ 1/ texture coord: 0 ~ 1

	unsigned int indices[6] = {
		0, 1, 3,    // 1st triangle
		1, 2, 3     // 2nd triangle
	};



	// Texture | Animator

	// Animator
	Animator* animator;

public:
	//Entity();
	Entity(int w, int h, std::string ct);
	Entity(glm::mat4 tr, int w, int h, std::string ct);

	void Generate();	// maybe tmp func
	void SetTextureSize(int w, int h);
	void SetColliderTransform(glm::mat4 mt, int w, int h);

	void LoadAnimator(std::string actor_name);

	void SetModel(glm::mat4 mat);//?
	void SetPosition(float x, float y);

	//virtual void Activate() = 0;
	virtual void Activate(double dt);

};

