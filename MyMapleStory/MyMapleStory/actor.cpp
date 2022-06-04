#include "actor.h"

Actor::Actor(int w, int h, std::string ct) : Entity(w, h, ct) {

}

Actor::~Actor() {
	std::cout << "Sys >> Actor Destructor\n";
}

//Actor::Actor(variables...){}




