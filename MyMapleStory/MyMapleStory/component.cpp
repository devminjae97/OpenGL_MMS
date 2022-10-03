#include "Component.h"

Component::Component(std::string compName) {
	name = compName;
}

Component::~Component() {
	delete owner;
}

void Component::SetOwner(Entity* e) {
	owner = e;
}

Entity* Component::GetOwner() const {
	return owner;
}

std::string Component::GetName() const {
	return name;
}
