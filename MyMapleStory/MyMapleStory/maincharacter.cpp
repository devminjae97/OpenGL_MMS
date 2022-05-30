#include "maincharacter.h"

MainCharacter::MainCharacter() : Actor(128, 128, "Type_MainCharacter") {
    // mc (width, height) = (128, 128)
    shader = new Shader("Shaders/characterShader.vs", "Shaders/characterShader.fs");

    Entity::LoadAnimator("Anim_MainCharacter");
    Entity::collision->setTransform(glm::vec3(0.f, -64.f, 0.f), 32, 64);

}

void MainCharacter::SetColliderTransform(glm::mat4 mt, int w, int h) {
    Actor::Entity::SetColliderTransform(mt, w, h);
}


void MainCharacter::Activate(double dt) {
    Entity::Activate(dt);

    GetKeyInput(dt);
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
                FaceRight(true);

                if (!is_jumping)
                    Entity::animator->SwitchAnimation("Anim_Walk");// SetAnim(ANIM_WALK);
            }

            mat_translate = glm::translate(mat_translate, vec_walk_unit * (float)dt * mainCharacter_speed * axis_horizontal_right);
            Entity::SetModel(mat_translate * mat_scale);
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
                Entity::animator->SwitchAnimation("Anim_Idle");// SetAnim(ANIM_IDLE);
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
                FaceRight(false);

                if (!is_jumping)
                    Entity::animator->SwitchAnimation("Anim_Walk");// SetAnim(ANIM_WALK);
            }

            mat_translate = glm::translate(mat_translate, vec_walk_unit * (float)dt * mainCharacter_speed * -axis_horizontal_left);
            Entity::SetModel(mat_translate * mat_scale);
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
                Entity::animator->SwitchAnimation("Anim_Idle");// SetAnim(ANIM_IDLE);
        }

        // axis
        if (axis_horizontal_left > 0.f)
            axis_horizontal_left -= dt * power_stop_axis_horizontal;
        else if (axis_horizontal_left < 0.f)
            axis_horizontal_left = 0.f;
    }


    // move
    if (is_key_right_pressed || is_key_left_pressed) {
        glm::vec4 vec = mat_translate * glm::vec4(1.0f);

        Entity::SetPosition(vec.x * Global::window_width, vec.y * Global::window_height);

        collision->SetModel(mat_translate);
    }


    //float axis_horizontal = axis_horizontal_right - axis_horizontal_left; // or L-R
    //if (axis_horizontal != 0.f) {

    //    mat_translate = glm::translate(mat_translate, vec_walk_unit * (float)dt * mainCharacter_speed * axis_horizontal);
    //    Entity::SetModel(mat_translate * mat_scale);

    //    //std::cout << "Axis Horizontal R: " << axis_horizontal_right << "\n";
    //}

    //printf("pos: (%f, %f)\n", transform.position.x, transform.position.y);

}

void MainCharacter::FaceRight(bool b) {
    if (!is_facing_right && b) {
        is_facing_right = true;
        mat_scale = glm::scale(glm::mat4(1.f), glm::vec3(-1.f, 1.f, 1.f));
    }
    else if (is_facing_right && !b) {
        is_facing_right = false;
        mat_scale = glm::mat4(1.f);
    }
}
