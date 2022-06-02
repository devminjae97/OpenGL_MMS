#include "texture_loader.h"

// 여기있어야 에러 안남..
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#endif
//---

unsigned int TextureLoader::LoadTexture(std::string target_full_size_path) {
    int texture_width, texture_height, nrChannels;

    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    unsigned char* data = stbi_load(target_full_size_path.c_str(), &texture_width, &texture_height, &nrChannels, 0);

    if (data) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set pixel store mode << ?
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        return tex;
    }
    else {
        return NONE;
    }
}

unsigned int TextureLoader::LoadTexture(std::string target_path, std::string name) {
    return LoadTexture(target_path + "_" + name + ".png");
}

std::vector<unsigned int> TextureLoader::LoadTextures(std::string target_path, std::string actor_name, std::string behaviour_name) {

    int texture_width, texture_height, nrChannels;

    std::vector<unsigned int> tmp;

    std::string path;

    for (int i = 0; ; i++) {
        unsigned int tex;

        path = target_path
            + actor_name + "_"
            + behaviour_name + "_"
            + std::to_string(i + 1) + ".png";

        tex = LoadTexture(path);

        if (tex == NONE) {
            break;
        }

        tmp.push_back(tex);
    }

    if (tmp.size() == 0) {
        std::cout << "ERROR::TEXTURE::LOADING_FALIED\n--path: " << path << "\n";
    }

    return tmp;
}