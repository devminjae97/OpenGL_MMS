#pragma once

#include "global.h"


//private:

class TextureLoader {
private:
	std::vector<unsigned int> textures;

public:
	static unsigned int LoadTexture(std::string target_full_size_path);
	static unsigned int LoadTexture(std::string target_path, std::string name);
	static std::vector<unsigned int> LoadTextures(std::string target_path, std::string actor_name, std::string behaviour_name);
};