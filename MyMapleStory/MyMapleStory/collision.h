#pragma once

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Collision {

private:
	glm::vec3 pos;
	float width;
	float height;

public:
	Collision(glm::mat4 tr, float w, float h) {
		pos = tr * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		width = w;
		height = h;
	}

		

};