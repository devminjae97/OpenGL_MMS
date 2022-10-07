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
	virtual void Awake() {};
	virtual void Update(double dt) {};
	virtual void Render() {};

	void SetOwner(Entity* e);
	Entity* GetOwner() const;
	
	std::string GetName() const;


protected:
	bool isUpdatable = true;

public:
	void EnableUpdate(bool b);
	bool GetUpdatability();
};