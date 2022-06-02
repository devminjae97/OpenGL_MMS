#pragma once

#include "object.h"

class Structure : public Object {
private:
public:
	Structure(int w, int h, std::string name);
	
	void Activate(double dt);


	void LoadSingleTexture(std::string name);



};