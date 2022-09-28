#include "mob.h"

Mob::Mob(int w, int h, std::string name, bool is_jump_enabled) : Actor(w, h, "Type_Monster") {

    shader = new Shader("Shaders/characterShader.vs", "Shaders/characterShader.fs");

    Entity::LoadAnimator("Anim_MainCharacter");
    Entity::collision->SetTransform(32, 64);

    if (is_jump_enabled)
        EnableJump();
}

Mob::~Mob() {
    delete collision_groundchecker;
}

void Mob::Update(double dt) {
    Entity::Update(dt);

    GroundCheck();

    FallResolution();

    ApplyGravity(dt);
    //CheckCollision();

    //SwitchMotion();


}

void Mob::EnableJump() {
    bool is_jump_enabled = true;

    collision_groundchecker = new Collision(30, 2, "Type_GroundChecker");
    collision_groundchecker->SetPosition(0, offset_y_collision_groundchecker);

    // Generate Anim_Jump ?
}

void Mob::SwitchMotion(double dt) {

    time_to_motion_change -= dt;
    time_to_jump -= dt;

    if (time_to_jump <= 0 && is_jump_enabled) {
        Jump();

        //time_to_jump = n??;
    }
    else if (time_to_motion_change <= 0) {
        current_motion = (int)(glfwGetTime() * 100) % num_motions + 1;

        switch (current_motion) {
        case 1: //idle
            animator->SwitchAnimation("Anim_Idle");
            break;
        case 2: //walk
            animator->SwitchAnimation("Anim_Walk");
            break;
        }


        time_to_motion_change = (int)(glfwGetTime() * 100) % 3 + 2;
    }

}

void Mob::Walk(double dt) {

}

void Mob::Jump() {
    if (!is_jumping) {
        is_jumping = true;

        velocity.y = jumpPower * 5.5f;

        animator->SwitchAnimation("Anim_Jump");
        time_to_jump = (int)(glfwGetTime() * 100) % 5 + 1 ;
    }
}

void Mob::GroundCheck() {
    collision_groundchecker->SetPosition(transform.position.x, transform.position.y + offset_y_collision_groundchecker);

    if (!Global::isHideCollision)
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


void Mob::ApplyGravity(double dt) {
    velocity.y -= gravity * (float)dt;
    if (velocity.y < terminal_velocity)
        velocity.y = terminal_velocity;

    Entity::AddPosition(0, (float)dt * velocity.y);
}

// Tmp
void Mob::FallResolution() {
    if (transform.position.y < -Global::window_width / 2) {
        SetPosition(0, 0);
    }
}