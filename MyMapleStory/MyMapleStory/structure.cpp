#include "structure.h"

Structure::Structure(int w, int h, std::string name) : Object(w, h, "Type_Structure") {
	shader = new Shader("Shaders/objectShader.vs", "Shaders/objectShader.fs");

	LoadSingleTexture(name);
}


void Structure::LoadSingleTexture(std::string name) {
	//tmp path?
	texture = TextureLoader::LoadTexture(std::string("Resources/object/" + name + ".png"));
}