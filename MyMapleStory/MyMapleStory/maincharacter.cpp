#include "maincharacter.h"

MainCharacter::MainCharacter() : Actor(128, 128, "Type_MainCharacter") {
    // mc (width, height) = (128, 128)
    shader = new Shader("Shaders/characterShader.vs", "Shaders/characterShader.fs");

    Entity::LoadAnimator("Anim_MainCharacter");
    Entity::collision->SetTransform(32, 64);

    collision_groundchecker = new Collision(30, 2, "Type_GroundChecker");
    collision_groundchecker->SetPosition(0, offset_y_collision_groundchecker);
}

MainCharacter::~MainCharacter() {
    std::cout << "Sys >> MainCharacter Destructor\n";

    delete collision_groundchecker;
}

void MainCharacter::Activate(double dt) {
    Entity::Activate(dt);

    GroundCheck();

    FallResolution();

    GetKeyInput(dt);
    ApplyGravity(dt);
    CheckCollision();

    SwitchAnimation();
    //test
    //printf("main character: (%.0f, %.0f)\n", transform.position.x, transform.position.y);
}

void MainCharacter::GetKeyInput(double dt) {
    if (glfwGetKey(Global::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Global::window, true);
    }

    Walk(dt);
    Jump();


    // reset position
    if (glfwGetKey(Global::window, GLFW_KEY_R) == GLFW_PRESS) {
        SetPosition(0, 0);
        velocity.y = 0;
        axis_horizontal = 0;
    }
}

void MainCharacter::Walk(double dt) {

    // Right 
    if (glfwGetKey(Global::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (!is_key_left_pressed) {
            if (!is_key_right_pressed) {
                is_key_right_pressed = true;
                Entity::Flip(true);
            }

            // axis
            if (axis_horizontal < 1.f) {
                if (is_jumping) {
                    axis_horizontal += dt * power_accel_axis_horizontal_on_air;
                }
                else {
                    axis_horizontal += dt * power_accel_axis_horizontal;
                }
            }
            else if (axis_horizontal > 1.f)
                axis_horizontal = 1.f;
        }
    }
    else if (glfwGetKey(Global::window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
        if (is_key_right_pressed) {
            is_key_right_pressed = false;
        }
    }

    // Left
    if (glfwGetKey(Global::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (!is_key_right_pressed) {
            if (!is_key_left_pressed) {
                is_key_left_pressed = true;
                Entity::Flip(false);
            }

            // axis
            if (axis_horizontal > -1.f)
                if (is_jumping) {
                    axis_horizontal -= dt * power_accel_axis_horizontal_on_air;
                }
                else {
                    axis_horizontal -= dt * power_accel_axis_horizontal;
                }
            else if (axis_horizontal < -1.f)
                axis_horizontal = -1.f;
        }

    }
    else if (glfwGetKey(Global::window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
        if (is_key_left_pressed) {
            is_key_left_pressed = false;
        }
    }

    //move
    if (axis_horizontal != 0) {
        Entity::AddPosition(vec_walk_unit.x * (float)dt * mainCharacter_speed * axis_horizontal, 0);
    }

    //stop

    if (!is_jumping) {
        if (is_key_right_pressed && axis_horizontal < 0 || is_key_left_pressed && axis_horizontal > 0) {
            axis_horizontal = 0;
        }
        else if(!is_key_right_pressed && !is_key_left_pressed) {
            if (abs(axis_horizontal) < 0.1f)
                axis_horizontal = 0;
            else if(axis_horizontal > 0)
                axis_horizontal -= dt * power_stop_axis_horizontal;
            else if(axis_horizontal < 0)
                axis_horizontal += dt * power_stop_axis_horizontal;
        }
    }



    //std::cout << "Tmp >> axis_horizontal = " << axis_horizontal << "\n";






    //test------------------------
    // UP
    if (glfwGetKey(Global::window, GLFW_KEY_UP) == GLFW_PRESS) {
        velocity.y = 0;
    }

    // DOWN
    if (glfwGetKey(Global::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    }
}

void MainCharacter::Jump() {
    if (glfwGetKey(Global::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!is_key_space_pressed)
            is_key_space_pressed = true;

        if (!is_jumping) {
            is_jumping = true;

            velocity.y = mainCharacter_jumpPower * 5.5f;
        }
    }
    else if (glfwGetKey(Global::window, GLFW_KEY_SPACE) == GLFW_RELEASE && is_key_space_pressed) {
        is_key_space_pressed = false;
    }
}

void MainCharacter::CheckCollision() {
    for (Collision* c : Collision::collisions) {
        if (c->GetType() == "Type_Structure" && c->GetIsBlockMode()) {
            if (c->CheckCollision(collision)) {
                CollisionResolution(c);
            }
        }
    }
}

void MainCharacter::CollisionResolution(Collision* other) {
    float overlapped_amount_x;
    float overlapped_amount_y;

    glm::vec2 pos_this = collision->GetPosition();
    glm::vec2 pos_other = other->GetPosition();
    glm::vec2 scale_this = collision->GetScale();
    glm::vec2 scale_other = other->GetScale();


    int horizontal = pos_this.x > other->GetPosition().x ? 1 : -1;
    int vertical = pos_this.y > other->GetPosition().y ? 1 : -1;
    
    overlapped_amount_x = abs((pos_this.x - horizontal * scale_this.x / 2) - (pos_other.x + horizontal * scale_other.x / 2));
    overlapped_amount_y = abs((pos_this.y - vertical * scale_this.y / 2) - (pos_other.y + vertical * scale_other.y / 2));

    // vertical
    if (overlapped_amount_x > overlapped_amount_y) {
        SetPosition(transform.position.x, pos_other.y + vertical * (scale_other.y / 2 + scale_this.y / 2));
        //gravity test
        //if(velocity.y < 0)
        velocity.y = 0;
    } 
    // horizontal
    else {
        SetPosition(pos_other.x + horizontal * (scale_other.x / 2 + scale_this.x / 2), transform.position.y);
        axis_horizontal = 0;
    }
}


void MainCharacter::SwitchAnimation() {
    if (is_jumping) {
        animator->SwitchAnimation("Anim_Jump");
    }
    else if (is_key_right_pressed || is_key_left_pressed) {
        animator->SwitchAnimation("Anim_Walk");
    }
    else {
        animator->SwitchAnimation("Anim_Idle");
    }
}

void MainCharacter::GroundCheck() {

    collision_groundchecker->SetPosition(transform.position.x, transform.position.y + offset_y_collision_groundchecker);

    if(!Global::isHideCollision)
        collision_groundchecker->Draw();

    for (Collision* c : Collision::collisions) {
        if (c->GetType() == "Type_Structure" && c->GetIsBlockMode()) {
            if (collision_groundchecker->CheckCollision(c)) {

                //jump-landing test
                if (is_jumping && collision->GetPosition().y > c->GetPosition().y) {
                    is_jumping = false;
                }
                return;
            }
        }
    }
    is_jumping = true;
}


void MainCharacter::ApplyGravity(double dt) {
    velocity.y -= gravity * (float)dt;
    if (velocity.y < terminal_velocity)
        velocity.y = terminal_velocity;

    Entity::AddPosition(0, (float)dt * velocity.y);
}

// Tmp
void MainCharacter::FallResolution() {
    if (transform.position.y < -Global::window_width / 2) {
        SetPosition(0, 0);
        //collision_groundchecker->SetPosition(transform.position.x, transform.position.y + offset_y_collision_groundchecker);
    }
}