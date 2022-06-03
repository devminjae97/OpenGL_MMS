#include "maincharacter.h"

MainCharacter::MainCharacter() : Actor(128, 128, "Type_MainCharacter") {
    // mc (width, height) = (128, 128)
    shader = new Shader("Shaders/characterShader.vs", "Shaders/characterShader.fs");

    Entity::LoadAnimator("Anim_MainCharacter");
    Entity::collision->setTransform(32, 64);

    //collision_groundchecker = new Collision(28, 4, "Type_GroundChecker");
    //collision_groundchecker->SetPosition(0, offset_y_collision_groundchecker);
}

void MainCharacter::Activate(double dt) {
    Entity::Activate(dt);


    //collision_groundchecker->SetPosition(transform.position.x, transform.position.y + offset_y_collision_groundchecker);
    //collision_groundchecker->Draw();

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

    // jump
    if (glfwGetKey(Global::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!is_key_space_pressed)
            is_key_space_pressed = true;

        if (!is_jumping) {
            is_jumping = true;
            velocity.y += mainCharacter_jumpPower * 5;
        }
    }
    else if (glfwGetKey(Global::window, GLFW_KEY_SPACE) == GLFW_RELEASE && is_key_space_pressed) {
        is_key_space_pressed = false;
    }

    Walk(dt);
}

void MainCharacter::Walk(double dt) {

    // Right 
    if (glfwGetKey(Global::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (!is_key_left_pressed) {
            if (!is_key_right_pressed) {
                is_key_right_pressed = true;
                Entity::Flip(true);
            }

            Entity::AddPosition(vec_walk_unit.x *Global::window_width* (float)dt * mainCharacter_speed * axis_horizontal_right, 0);
        }

        // axis
        if (axis_horizontal_right < 1.f)
            axis_horizontal_right += dt * power_accel_axis_horizontal;
        else if (axis_horizontal_right > 1.f)
            axis_horizontal_right = 1.f;
    }
    else if (glfwGetKey(Global::window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
        if (is_key_right_pressed) {
            is_key_right_pressed = false;
        }

        // axis
        if (axis_horizontal_right > 0.f)
            axis_horizontal_right -= dt * power_stop_axis_horizontal;
        else if (axis_horizontal_right < 0.f)
            axis_horizontal_right = 0.f;
    }

    // Left
    if (glfwGetKey(Global::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (!is_key_right_pressed) {
            if (!is_key_left_pressed) {
                is_key_left_pressed = true;
                Entity::Flip(false);
            }

            Entity::AddPosition(vec_walk_unit.x * Global::window_width * (float)dt * mainCharacter_speed * -axis_horizontal_left, 0);
        }

        // axis
        if (axis_horizontal_left < 1.f)
            axis_horizontal_left += dt * power_accel_axis_horizontal;
        else if (axis_horizontal_left > 1.f)
            axis_horizontal_left = 1.f;

    }
    else if (glfwGetKey(Global::window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
        if (is_key_left_pressed) {
            is_key_left_pressed = false;
        }

        // axis
        if (axis_horizontal_left > 0.f)
            axis_horizontal_left -= dt * power_stop_axis_horizontal;
        else if (axis_horizontal_left < 0.f)
            axis_horizontal_left = 0.f;
    }



    //test------------------------
    // UP
    if (glfwGetKey(Global::window, GLFW_KEY_UP) == GLFW_PRESS) {
        Entity::AddPosition(0, vec_walk_unit.x * Global::window_width * (float)dt * mainCharacter_speed);
        velocity.y = 0;
    }

    // DOWN
    if (glfwGetKey(Global::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        //Entity::AddPosition(0, vec_walk_unit.x * Global::window_width * (float)dt * -mainCharacter_speed);
        //test
        SetPosition(0, 0);
        velocity.y = 0;
    }




    //printf("pos: (%.1f, %.1f)\n", transform.position.x, transform.position.y);

}

void MainCharacter::CheckCollision() {

    // !need to change Collision::CheckCollisionByType!
    for (Collision* c : Collision::collisions) {
        if (c->GetType() == "Type_Structure") {

            if (c->checkCollision(collision)) {
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
        if(velocity.y < 0)
            velocity.y = 0;

        //jump-landing test
        if (is_jumping && vertical > 0) {
            is_jumping = false;
        }
    } 
    // horizontal
    else {
        SetPosition(pos_other.x + horizontal * (scale_other.x / 2 + scale_this.x / 2), transform.position.y);
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
    float pos_y = collision->GetPosition().y + collision->GetScale().y;
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