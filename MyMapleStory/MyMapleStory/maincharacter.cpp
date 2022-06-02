#include "maincharacter.h"

MainCharacter::MainCharacter() : Actor(128, 128, "Type_MainCharacter") {
    // mc (width, height) = (128, 128)
    shader = new Shader("Shaders/characterShader.vs", "Shaders/characterShader.fs");

    Entity::LoadAnimator("Anim_MainCharacter");
    Entity::collision->setTransform(glm::vec3(0.f, -32.f, 0.f), 32, 64);

}

void MainCharacter::Activate(double dt) {
    Entity::Activate(dt);

    GetKeyInput(dt);
    CheckCollision();






    // Last
    SavePrevPosition();

    //test
    //printf("main character: (%.0f, %.0f)\n", transform.position.x, transform.position.y);
}

void MainCharacter::GetKeyInput(double dt) {
    if (glfwGetKey(Global::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Global::window, true);
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

                if (!is_jumping)
                    Entity::animator->SwitchAnimation("Anim_Walk");
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

            if (!is_jumping)
                Entity::animator->SwitchAnimation("Anim_Idle");
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

                if (!is_jumping)
                    Entity::animator->SwitchAnimation("Anim_Walk");
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

            if (!is_jumping)
                Entity::animator->SwitchAnimation("Anim_Idle");
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
    }

    // DOWN
    if (glfwGetKey(Global::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        Entity::AddPosition(0, vec_walk_unit.x * Global::window_width * (float)dt * -mainCharacter_speed);
    }




    //printf("pos: (%.1f, %.1f)\n", transform.position.x, transform.position.y);

}




void MainCharacter::SavePrevPosition() {
    prev_x = transform.position.x;
    prev_y = transform.position.y;
}

void MainCharacter::CheckCollision() {


    for (Collision* c : Collision::collisions) {
        if (c->GetType() == "Type_Structure") {

            if (collision->checkCollision(c)) {
                CollisionResolution(c);
            }
        }
    }

}

void MainCharacter::CollisionResolution(Collision* c) {

    float overlapped_amount_x;
    float overlapped_amount_y;

    // -----------------------------------------------------------------------<1>
    // in c's view, main character is ...
    //bool is_on_right = transform.position.x > c->GetPosition().x ? true : false;
    //bool is_on_top = transform.position.y > c->GetPosition().y ? true : false;


    //// Right, Top
    //if (is_on_right && is_on_top) {

    //}
    //// Left, Top
    //else if (!is_on_right && is_on_top) {

    //}
    //// Left, Bottom
    //else if (!is_on_right && !is_on_top) {

    //}
    //// Right, Bottom
    //else if (is_on_right && !is_on_top) {

    //}


    // -----------------------------------------------------------------------<2>
    int vertical = collision->GetPosition().x > c->GetPosition().x ? 1 : -1;
    int horizontal = collision->GetPosition().y > c->GetPosition().y ? 1 : -1;

    overlapped_amount_x = (collision->GetPosition().x - vertical * collision->GetScale().x/2) - (c->GetPosition().x + vertical * c->GetScale().x/2);
    overlapped_amount_y = (collision->GetPosition().y - horizontal * collision->GetScale().y/2) - (c->GetPosition().y + vertical * c->GetScale().y/2);


    //overlapped amount 값 이상함

    std::cout << "OLM: " << overlapped_amount_x << " // " << overlapped_amount_y << "\n";

    if (abs(overlapped_amount_x) > abs(overlapped_amount_y)) {
        ;// SetPosition()
    }
    else {

    }


    
}