#pragma once

#include "component.h"
#include "shader.h"

class Collider : public Component {
	//-----------------------------------
	// <Static>
private:
	static std::vector<Collider*> colliders;


	/*
	
	do i need to seperate overlap and collision?
	
	*/






	//-----------------------------------
	// <Member>

	// Shader
	Shader* shader;

	// GL variables
	unsigned int VBO, VAO, EBO;

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
	bool is_block_mode;


	// type; main character, monster, land(map), portal, ...
	std::string type = "Type_Default";	// tag?

	glm::vec3 offset = glm::vec3(0.f);
	glm::vec3 offset_ratio = glm::vec3(0.f);
	glm::mat4 mat_model = glm::mat4(1.f);
	//glm::mat4 trans = glm::mat4(1.f);

	float x;
	float y;

	// Actually, half of real width or height value
	int width;
	int height;

	std::vector<Collider*> overlapped_collisions = std::vector<Collider*>();









public:
	Collider(std::string name) : Component(name) {};

public:
	virtual void Awake() override;
	virtual void Update() override;


private:
	std::string tag = "default";	// enum?
public:
	std::string GetTag() const;


public:
	//Collision();
	//Collider(int w, int h, std::string ct);

	void Generate();	// maybe tmp func
	void SetTextureSize(int w, int h);

	void SetBlockMode(bool b);
	void SetOffset(glm::vec3 offset);	// offset location
	void SetScale(int w, int h);	// size
	void SetPosition(float x, float y);	// == entity position
	void SetModel(glm::mat4 mat);
	void LoadCollisionTexture();

	bool GetIsBlockMode();
	std::string GetType();

	glm::vec2 GetPosition();
	glm::vec2 GetScale();


	// to where?
	bool isUpdatable = true;	// 단어가 이게 맞나?





	//bool CheckCollision(std::string tag);
	
	
	bool CheckCollision(Collider* c);



	// Basic functions
	virtual void Awake() override;
	virtual void Update() override;
	void Draw();	// rename to render?
};