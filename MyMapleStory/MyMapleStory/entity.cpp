#include "entity.h"

//Entity::Entity() {
//	collision = Collision(glm::mat4(1.f), 0, 0, "empty");
//}

Entity::Entity(int w, int h, std::string ct) {
    transform.width = w;
    transform.height = h;
    collision = new Collision(w, h, ct);    // πË∞Ê¿∫?

    Generate();
}

Entity::~Entity() {
    std::cout << "Sys >> Entity Destructor\n";
    delete shader;
    delete animator;
    delete collision;
}

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

void Entity::SetColliderBlockMode(bool b) {
    collision->SetBlockMode(b);
}

void Entity::LoadAnimator(std::string actor_name) {
    animator = new Animator(actor_name);
}

void Entity::Activate(double dt) {
    shader->use();
    shader->setMat4("model", mat_model);

    glBindVertexArray(VAO);
    animator->PlayAnimation(dt);    //glBindTexture(...);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // draw collider
    if (!Global::isHideCollision)
        collision->Draw();
}

void Entity::SetModel(glm::mat4 trans, glm::mat4 scale) {
    mat_model = trans * scale;

    glm::vec4 vec = trans * glm::vec4(1.0f);

}

void Entity::SetPosition(float x, float y) {
    transform.position.x = x;
    transform.position.y = y;

    glm::mat4 trans = glm::translate(glm::mat4(1.f), glm::vec3((float)x / Global::window_width * 2, (float)y / Global::window_height * 2, 0.f));
    glm::mat4 scale = transform.is_flip ? glm::scale(glm::mat4(1.f), glm::vec3(-1.f, 1.f, 1.f)) : glm::mat4(1.f);
    SetModel(trans, scale);


    // move collision
    collision->SetPosition(x, y);
}

void Entity::AddPosition(float x, float y) {
    SetPosition(transform.position.x + x, transform.position.y + y);
}

void Entity::Flip(bool b) {
    transform.is_flip = b;
}