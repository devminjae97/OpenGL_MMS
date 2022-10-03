#pragma once

#include "global.h"

class Entity;
class Component {
protected:
	std::string name;
	Entity* owner;


	Component(std::string comp_name);
	virtual ~Component();

public:
	void SetOwner(Entity* e);
	Entity* GetOwner() const;
	
	std::string GetName() const;

	virtual void Awake() {};
	virtual void Update() {};
};