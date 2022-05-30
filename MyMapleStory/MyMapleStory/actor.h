#pragma once

#include "entity.h"
//#include "animator.h"

class Actor : public Entity {

private:



	// Basic variables
	float speed = 100;
	float hp = 50;
	float mp = 5;

public:
	Actor(int w, int h, std::string ct);
	//void LoadAnimator(std::string actor_name);
	void InitTexture();
	virtual void Activate(double dt) = 0;

};