#pragma once

#include "entity.h"

class Object : public Entity {
protected:

	// texture
	unsigned int texture = NONE;


public:
	Object(int w, int h, std::string ct);
	
//	void SetPosotion(int x, int y);
	virtual void Activate(double dt) = 0;

};