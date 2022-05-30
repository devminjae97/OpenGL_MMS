#include "collision.h"


unsigned int Collision::count = 0;

//Collision::Collision() {}

Collision::Collision(int w, int h, std::string ct) {
	id = count++;

	isBlockMode = false;
	type = ct;


	Generate();
	setTransform(w, h);
	LoadCollisionTexture();
}

// delete?
//Collision::Collision(glm::mat4 tr, int w, int h, std::string ct) {
//	id = count++;
//
//	isBlockMode = false;
//	type = ct;
//
//	//printf("create collision :: id:%d\n", id);
//
//	//setTransform(tr, w, h);
//	Generate();
//	LoadCollisionTexture();
//}
//
//// delete?	+bool
//Collision::Collision(glm::mat4 tr, int w, int h, std::string ct, bool b) {
//	id = count++;
//
//	isBlockMode = b;
//	type = ct;
//
//	//printf("create collision :: id:%d\n", id);
//
//	//setTransform(tr, w, h);
//}

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

void Collision::setTransform(glm::vec3 offset) {
	//glm::vec3 pos = tr * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//x = pos.x;
	//y = pos.y;
	offset_ratio = glm::vec3(offset.x / Global::window_width, offset.y / Global::window_height, 0.f);
}

void Collision::setTransform(int w, int h) {
	width = w;
	height = h;
	SetTextureSize(w, h);
}

void Collision::setTransform(glm::vec3 offset, int w, int h) {
	setTransform(offset);
	setTransform(w, h);
}

void Collision::SetModel(glm::mat4 mat) {
	mat_model = mat;
}

void Collision::LoadCollisionTexture() {
	texture = TextureLoader::LoadTexture(std::string("Resources/test/collision_full.png"));
}

void Collision::setBlockMode(bool b) {
	isBlockMode = b;
}

bool Collision::getIsBlocked() {
	return isBlockMode;
}

void Collision::Draw(/*position*/) {
	if (texture != NONE) {
		// line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		shader->use();

		glm::mat4 trans = glm::translate(mat_model, offset_ratio);
		shader->setMat4("model", trans);

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 복원
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Collision::checkCollision(Collision c) {
	if (abs(x - c.x) < width + c.width && abs(y - c.y) < height + c.height) {
		// call once
		if (!isOverlapped) {
			//std::cout << "COLLISION::OVERLAP_BEGIN\n";
			isOverlapped = true;

			//test
			if (this->type == "Type_MainCharacter" && c.getIsBlocked()) {
				collide(c);
			}
		}
	}
	else if (isOverlapped) {
		//std::cout << "COLLISION::OVERLAP_END\n";

		isOverlapped = false;
	}
}

void Collision::collide(Collision c) {

}