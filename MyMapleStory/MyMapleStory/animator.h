#pragma once

#include "global.h"
#include "texture_loader.h"

struct Animation {
	std::string animation_name;
	std::vector<unsigned int> textures;
	double switching_time;
};

class Animator {
private:

	const char* path_maincharacter = "Resources/avatar/";

	std::vector<Animation> animation_pool;
	Animation current_animation;

	// info from Animation struct
	double switching_time = .57f;
	int texture_count = 0;

	// variables for play animation
	double delta_time = 0;
	int texture_index = 0;


public:
	Animator(std::string str);

	void LoadMainCharacterTextures();
	void LoadTextures(std::string target_path, std::string anim_name);

	void InitAnim();	// set idle animation
	void SwitchAnimation(std::string anim_name);
	void PlayAnimation(double dt);

	void SetFrameSwitchingTime(std::string name, double t);	// ???

};