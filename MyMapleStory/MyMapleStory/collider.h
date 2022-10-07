#pragma once

#include "component.h"

class Shader;
class Collider : public Component {
	//-----------------------------------
	// <Static>
private:
	static std::vector<Collider*> colliders;


	//-----------------------------------
	// <Member>

	// basic
public:
	Collider(std::string name);
	~Collider();

	virtual void Awake() override;
	virtual void Update(double dt) override;
	virtual void Render() override;


	// shader
private:
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

	void InitShader();


	// texture
private:
	unsigned int texture = NONE;
	unsigned int texture_hit = NONE;

	void LoadTexture();


	// transform
private:
	float x;
	float y;

	int width;
	int height;

	glm::vec3 offset = glm::vec3(0.f);
	glm::vec3 offset_ratio = glm::vec3(0.f);
	glm::mat4 mat_model = glm::mat4(1.f);

	void SetPosition(float x, float y);	// == entity position >> move? update?

public:
	void SetScale(int w, int h);	// size
	void SetOffset(float x, float y);	// offset of location
	//void SetModel(glm::mat4 mat);

	glm::vec2 GetPosition();
	glm::vec2 GetScale();


	// settings
private:
	std::string tag = "Default";
	bool isBlockMode = false;

public:
	void SetTag(std::string compTag);
	std::string GetTag() const;
	void SetBlockMode(bool b);
	//bool GetIsBlockMode();


	// overlap, collision
private:
	bool isOverlapped = false;

	//bool CheckCollision(std::string tag);
	void CheckOverlaps();
	bool CheckOverlap(const Collider* c);
};