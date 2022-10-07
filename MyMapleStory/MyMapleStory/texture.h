#pragma once

#include "component.h"

class Shader;
class Texture : public Component {

public:
	Texture(std::string name);
	~Texture();

	virtual void Awake() override;
	virtual void Update(double dt) override;
	virtual void Render() override;


	// texture
private:
	unsigned int texture = NONE;

public:
	void LoadTexture(std::string path);


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

	glm::mat4 mat_model = glm::mat4(1.f);

public:
	void InitShader();


};