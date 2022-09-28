#include "animator.h"


Animator::Animator(std::string str) {
    if (str == "Anim_MainCharacter") {
        std::cout << "Animator::Animator(main character)\n";
        LoadMainCharacterTextures();
    }
    else if (str == "Anim_Mob") {
        std::cout << "Animator::Animator(mob)\n";
    }
    else {
        std::cout << "Animator::Animator(else)\n";
    }
}

void Animator::LoadMainCharacterTextures() {

    int texture_width, texture_height, nrChannels;
    Animation anim;


    // Idle: 4 sprites
    anim = Animation();
    anim.textures = TextureLoader::LoadTextures(path_maincharacter, std::string("avatar"), std::string("idle"));
    if (anim.textures.size() > 0) {
        anim.animation_name = "Anim_Idle";
        anim.switching_time = 0.57f;
        animation_pool.push_back(anim);
    }


    // Walk: 4 sprites
    anim = Animation();
    anim.textures = TextureLoader::LoadTextures(path_maincharacter, std::string("avatar"), std::string("walk"));
    if (anim.textures.size() > 0) {
        anim.animation_name = "Anim_Walk";
        anim.switching_time = 0.15f; //-0.001875 * mainCharacter_speed + 0.45f;  // 160->0.15f, 80->0.3f
        animation_pool.push_back(anim);
    }



    // Jump: 1 sprite
    anim = Animation();
    anim.textures = TextureLoader::LoadTextures(path_maincharacter, std::string("avatar"), std::string("jump"));
    if (anim.textures.size() > 0) {
        anim.animation_name = "Anim_Jump";
        anim.switching_time = 99.f;
        animation_pool.push_back(anim);
    }



    // Init
    InitAnim();
}

void Animator::LoadTextures(std::string target_path, std::string anim_name) {

    int texture_width, texture_height, nrChannels;
    Animation anim;


    // Idle: n sprites
    anim = Animation();
    anim.textures = TextureLoader::LoadTextures(target_path, anim_name, std::string("idle"));
    if (anim.textures.size() > 0) {
        anim.animation_name = "Anim_Idle";
        anim.switching_time = 0.57f;
        animation_pool.push_back(anim);
    }
}

void Animator::LoadTexture(std::string target_path/*, std::string anim_name*/) {

    int texture_width, texture_height, nrChannels;
    Animation anim;
    unsigned int tmp;


    // Single sprite
    anim = Animation();
    tmp = TextureLoader::LoadTexture(target_path);
    if (tmp != NONE) {
        anim.textures.push_back(tmp);
        anim.animation_name = "Texture";    // get name from parameter
        anim.switching_time = NONE;    // test
        animation_pool.push_back(anim);

        // Init
        InitAnim();
    }
    else {
        std::cout << "ERROR::ANIMATION::LOAD_FALIED\n--path: " << target_path << "\n";
    }

}

void Animator::InitAnim() {
    if (animation_pool.size() > 0) {
        current_animation = animation_pool[0];

        switching_time = current_animation.switching_time;
        texture_count = current_animation.textures.size();

        delta_time = 0;
        texture_index = 0;
    }
}

void Animator::SwitchAnimation(std::string anim_name) {
    for (int i = 0; ; i++) {
        if (i >= animation_pool.size()) {
            std::cout << "ERROR::ANIMATION::SWITCHING_FALIED\n--anim_name: " << anim_name << "\n";
            break;
        }
        else if (animation_pool[i].animation_name == anim_name) {
            if (current_animation.animation_name != anim_name) {

                current_animation = animation_pool[i];

                switching_time = current_animation.switching_time;
                texture_count = current_animation.textures.size();

                delta_time = 0;
                texture_index = 0;
            }

            break;
        }
    }
}

void Animator::PlayAnimation(double dt) {
    if (current_animation.textures.size() == 1) {
        glBindTexture(GL_TEXTURE_2D, current_animation.textures[0]);
    }
    else if (current_animation.textures.size() > 1) {
        delta_time += dt;


        if (delta_time >= switching_time) {
            delta_time = 0;
            texture_index == (texture_count - 1) ? texture_index = 0 : texture_index++;

        }

        glBindTexture(GL_TEXTURE_2D, current_animation.textures[texture_index]);


        //        glBindVertexArray(oVAO);
        //        glBindTexture(GL_TEXTURE_2D, oTex);
        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    else {
        std::cout << "ERROR::ANIMATION::PLAYING_FALIED\n";
    }
}