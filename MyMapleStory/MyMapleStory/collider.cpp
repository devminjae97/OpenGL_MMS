#include "collider.h"
#include "shader.h"
#include "texture_loader.h"
#include "entity.h"

Collider::Collider(std::string name) : Component(name) {
	InitShader();
	LoadTexture();
	colliders.emplace_back(this);
}

Collider::~Collider() {
	delete shader;
}

void Collider::Awake(){

}

void Collider::Update(double dt) {
	if (isUpdatable) {
		CheckOverlaps();
	}
}

void Collider::Render() {
	if (texture != NONE && texture_hit != NONE) {
		// Line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glm::mat4 trans = glm::translate(mat_model, offset_ratio);

		shader->use();
		shader->setMat4("model", trans);

		glBindVertexArray(VAO);
		if (isOverlapped)
			glBindTexture(GL_TEXTURE_2D, texture_hit);
		else
			glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Collider::InitShader() {
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

void Collider::LoadTexture() {
	texture = TextureLoader::LoadTexture(std::string("Resources/test/collision_full.png"));
	texture_hit = TextureLoader::LoadTexture(std::string("Resources/test/collision_hit.png"));
}

void Collider::SetPosition(float x, float y) {
	this->x = x + offset.x;
	this->y = y + offset.y;

	mat_model = glm::translate(glm::mat4(1.f), glm::vec3((float)x / Global::window_width * 2, (float)y / Global::window_height * 2, 0.f));
}

void Collider::SetScale(int w, int h) {
	width = w;
	height = h;

	float width_ratio = (float)w / Global::window_width;
	float height_ratio = (float)h / Global::window_height;

	vertices[0] = width_ratio;
	vertices[8] = width_ratio;
	vertices[16] = -width_ratio;
	vertices[24] = -width_ratio;

	vertices[1] = height_ratio;
	vertices[9] = -height_ratio;
	vertices[17] = -height_ratio;
	vertices[25] = height_ratio;

	// Update vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Collider::SetOffset(float x, float y) {
	offset = glm::vec3(x, y, 0);
}

glm::vec2 Collider::GetPosition() {
	return glm::vec2(x, y);
}

glm::vec2 Collider::GetScale() {
	return glm::vec2(width, height);
}

void Collider::SetTag(std::string tag) {
	this->tag = tag;
}

std::string Collider::GetTag() const {
	return tag;
}

void Collider::SetBlockMode(bool b) {
	isBlockMode = b;
}

void Collider::CheckOverlaps() {
	isOverlapped = false;

	for (Collider* c : colliders) {
		if (this == c)
			continue;

		if (CheckOverlap(c)) {
			owner->OnOverlap(c);
			isOverlapped = true;
		}
	}
}

bool Collider::CheckOverlap(const Collider* c) {
	bool isOverlapped_x = abs(x - c->x) * 2 < width + c->width;
	bool isOverlapped_y = abs(y - c->y) * 2 < height + c->height;

	return  isOverlapped_x && isOverlapped_y;
}

std::vector<Collider*> Collider::colliders;