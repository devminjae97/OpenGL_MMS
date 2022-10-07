#include "Component.h"
#include "entity.h"

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

void Component::EnableUpdate(bool b) {
	isUpdatable = b;
}

bool Component::GetUpdatability() {
	return isUpdatable;
}
