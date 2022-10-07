#include "actor.h"

Actor::Actor(int w, int h, std::string ct) : Entity(w, h, ct) {

}

Actor::~Actor() {
	std::cout << "Sys >> Actor Destructor\n";
}

//Actor::Actor(variables...){}

void Actor::Render(double dt) {
    shader->use();
    shader->setMat4("model", mat_model);

    glBindVertexArray(VAO);
    animator->PlayAnimation(dt);    //glBindTexture(...);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // draw collider
    if (!Global::isHideCollision) {
        collision->Draw();
    }
}
