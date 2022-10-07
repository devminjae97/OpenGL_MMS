#include "texture.h"
#include "shader.h"
#include "texture_loader.h"

Texture::Texture(std::string name) : Component(name) {
	InitShader();
}

Texture::~Texture() {
	delete shader;
}

void Texture::Awake() {

}

void Texture::Update(double dt) {
	if (isUpdatable) {

	}
}

void Texture::Render() {
	shader->use();
	shader->setMat4("model", mat_model);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Texture::InitShader() {
	shader = new Shader("Shaders/objectShader.vs", "Shaders/objectShader.fs");

	// Vertex Buffer Object, Vertex Array Object, Element Buffer Object
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Texture::LoadTexture(std::string path) {
	texture = TextureLoader::LoadTexture(path);
}