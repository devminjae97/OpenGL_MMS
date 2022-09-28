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
	~Actor();

	//void LoadAnimator(std::string actor_name);
	//void InitTexture();

	// update : Somegthing might be shared btw mob and charcter...
	//virtual void Update(double dt) = 0;
	virtual void Render(double dt);

};