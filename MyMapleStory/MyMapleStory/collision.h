#pragma once

#include "global.h"
#include "shader.h"
#include "texture_loader.h"


class Collision {


	//-------------------------
	// static
private:
	static unsigned int count;

public:
	static std::vector<Collision*> collisions;


private:

	int id;

	// Shader
	Shader* shader;

	// GL variables
	unsigned  int VBO, VAO, EBO;

	float vertices[32] = {
		.5f, .5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,     // RT
		.5f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,     // RB
		-.5f, -.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // LB
		-.5f, .5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // LT
	};  // range >> position: -1 ~ 1/ colour: 0 ~ 1/ texture coord: 0 ~ 1

	unsigned int indices[6] = {
		0, 1, 3,    // 1st triangle
		1, 2, 3     // 2nd triangle
	};

	// texture
	unsigned int texture = NONE;
	unsigned int texture_hit = NONE;



	// setting
	bool isBlockMode;


	// type; main character, monster, land(map), portal, ...
	std::string type = "Type_Default";

	glm::vec3 offset = glm::vec3(0.f);
	glm::vec3 offset_ratio = glm::vec3(0.f);
	glm::mat4 mat_model = glm::mat4(1.f);
	//glm::mat4 trans = glm::mat4(1.f);

	//delete?
	float x;
	float y;

	// Actually, half of real width or height value
	int width;
	int height;

	bool is_overlapped = false;	// 하나밖에 못담음



public:
	//Collision();
	Collision(int w, int h, std::string ct);
	Collision(glm::mat4 tr, int w, int h, std::string ct);
	Collision(glm::mat4 tr, int w, int h, std::string ct, bool b);

	void Generate();	// maybe tmp func
	void SetTextureSize(int w, int h);

	void setBlockMode(bool b);
	void SetOffset(glm::vec3 offset);	// location
	void setTransform(int w, int h);	// size
	void setTransform(glm::vec3 offset, int w, int h);
	void SetPosition(float x, float y);
	void SetModel(glm::mat4 mat);
	void LoadCollisionTexture();

	bool getIsBlocked();
	std::string GetType();

	glm::vec2 GetPosition();
	glm::vec2 GetScale();

	void Draw();

	bool checkCollision(Collision* c);
	bool CheckCollisionByType(std::string type);

};