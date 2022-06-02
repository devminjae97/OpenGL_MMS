#include "structure.h"

Structure::Structure(int w, int h, std::string name) : Object(w, h, "Type_Structure") {
	shader = new Shader("Shaders/objectShader.vs", "Shaders/objectShader.fs");

	LoadSingleTexture(name);
}

void Structure::Activate(double dt) {
	// tmp code

	shader->use();
	shader->setMat4("model", mat_model);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// draw collider
	if (!Global::isHideCollision)
		collision->Draw();
}

void Structure::LoadSingleTexture(std::string name) {
	//tmp path?
	texture = TextureLoader::LoadTexture(std::string("Resources/object/" + name + ".png"));
}