#include "entity.h"

//Entity::Entity() {
//	collision = Collision(glm::mat4(1.f), 0, 0, "empty");
//}

Entity::Entity(int w, int h, std::string ct) {
    transform.width = w;
    transform.height = h;
    collision = new Collision(10, h, ct);

    Generate();
}

// delete?
//Entity::Entity(glm::mat4 tr, int w, int h, std::string ct) {
//    transform.width = w;
//    transform.height = h;
//	//collision = new Collision(tr, (float) w / Global::window_width, (float) h / Global::window_height, ct);
//	collision = new Collision(tr, w, h, ct);
//
//    Generate();
//}

void Entity::Generate() {


    SetTextureSize(transform.width, transform.height);

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


void Entity::SetTextureSize(int w, int h) {

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
}

void Entity::SetColliderTransform(glm::mat4 mt, int w, int h) {
    //collision->SetSize(w, h);
}

void Entity::LoadAnimator(std::string actor_name) {

    animator = new Animator(actor_name);
}

void Entity::Activate(double dt) {

    // calculate matrix; translate * scale




    shader->use();
    shader->setMat4("model", mat_model);

    glBindVertexArray(VAO);
    animator->PlayAnimation(dt);    //glBindTexture(...);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // draw collider
    if (!Global::isHideCollision)
        collision->Draw(/*position*/);
}

void Entity::SetModel(glm::mat4 mat) {
    mat_model = mat;
}

void Entity::SetPosition(float x, float y) {
    transform.position.x = x;
    transform.position.y = y;
}