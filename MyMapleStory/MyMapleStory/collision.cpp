#include "collision.h"


unsigned int Collision::count = 0;
std::vector<Collision*> Collision::collisions = std::vector<Collision*>();

//Collision::Collision() {}

Collision::Collision(int w, int h, std::string ct) {
	id = count++;

	is_block_mode = false;
	type = ct;


	Generate();
	SetTransform(w, h);
	LoadCollisionTexture();

	collisions.push_back(this);
}

void Collision::Generate() {

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

void Collision::Draw() {
	if (texture != NONE) {
		// line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glm::mat4 trans = glm::translate(mat_model, offset_ratio);

		shader->use();
		shader->setMat4("model", trans);

		glBindVertexArray(VAO);
		if(overlapped_collisions.size() > 0)
			glBindTexture(GL_TEXTURE_2D, texture_hit);
		else
			glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 복원
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Collision::SetTextureSize(int w, int h) {

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

// 정리 필요 settexturesize <--> settransform

void Collision::SetOffset(glm::vec3 offset) {
	this->offset = offset;
	offset_ratio = glm::vec3(offset.x / Global::window_width * 2, offset.y / Global::window_height * 2, 0.f);
}

void Collision::SetTransform(int w, int h) {
	width = w;
	height = h;
	SetTextureSize(w, h);
}

void Collision::SetTransform(glm::vec3 offset, int w, int h) {
	SetOffset(offset);
	SetTransform(w, h);
}

void Collision::SetPosition(float x, float y) {
	this->x = x + offset.x;
	this->y = y + offset.y;
		
    glm::mat4 trans = glm::translate(glm::mat4(1.f), glm::vec3((float)x / Global::window_width * 2, (float)y / Global::window_height * 2, 0.f));
	SetModel(trans);
}

void Collision::SetModel(glm::mat4 mat) {
	mat_model = mat;
}

void Collision::LoadCollisionTexture() {
	texture = TextureLoader::LoadTexture(std::string("Resources/test/collision_full.png"));
	texture_hit = TextureLoader::LoadTexture(std::string("Resources/test/collision_hit.png"));
}

void Collision::SetBlockMode(bool b) {
	is_block_mode = b;
}

bool Collision::GetIsBlockMode() {
	return is_block_mode;
}

std::string Collision::GetType() {
	return type;
}

glm::vec2 Collision::GetPosition() {
	return glm::vec2(x, y);
}

glm::vec2 Collision::GetScale() {
	return glm::vec2(width, height);
}


bool Collision::CheckCollision(Collision* c) {
	if (abs(x - c->x) < width / 2 + c->width / 2 && abs(y - c->y) < height / 2 + c->height / 2) {
		// call once

		std::vector<Collision*>::iterator it;
		it = std::find(overlapped_collisions.begin(), overlapped_collisions.end(), c);
		if (it == overlapped_collisions.end()) {
			std::cout << "COLLISION::OVERLAP_BEGIN\n";
			overlapped_collisions.push_back(c);
		}
		return true;
	}
	else {
		std::vector<Collision*>::iterator it;
		it = std::find(overlapped_collisions.begin(), overlapped_collisions.end(), c);
		if (it != overlapped_collisions.end()) {
			std::cout << "COLLISION::OVERLAP_END\n";
			overlapped_collisions.erase(it);
		}
		return false;
	}
	return false;
}
