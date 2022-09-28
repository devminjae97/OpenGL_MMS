#pragma once

#include "object.h"

class Structure : public Object {
private:
public:
	Structure(int w, int h, std::string name);

	void Update(double dt);
	//void Render(double dt);


	void LoadSingleTexture(std::string name);



};