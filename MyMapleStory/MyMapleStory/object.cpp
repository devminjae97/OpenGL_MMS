#include "object.h"

Object::Object(int w, int h, std::string ct) : Entity(w, h, ct) {

}

void Object::Render(double dt) {
	// tmp code

	shader->use();
	shader->setMat4("model", mat_model);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// draw collider
	if (!Global::isHideCollision) {
		collision->Draw();
	}
}