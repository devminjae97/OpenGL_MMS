#include "collision.h"


unsigned int Collision::count = 0;

Collision::Collision(glm::mat4 tr, float w, float h) {
	id = count++;

	isBlockMode = false;

	//printf("create collision :: id:%d\n", id);

	glm::vec3 pos = tr * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	x = pos.x;
	y = pos.y;

	width = w;
	height = h;
}

Collision::Collision(glm::mat4 tr, float w, float h, bool b) {
	id = count++;

	isBlockMode = b;

	//printf("create collision :: id:%d\n", id);

	glm::vec3 pos = tr * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	x = pos.x;
	y = pos.y;

	width = w;
	height = h;
}

void Collision::setTrans(glm::mat4 tr) {
	glm::vec3 pos = tr * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	x = pos.x;
	y = pos.y;


}

void Collision::setBlockMode(bool b) {
	isBlockMode = b;
}


void Collision::checkCollision(Collision c) {
	if (abs(x - c.x) < width + c.width && abs(y - c.y) < height + c.height) {
		// call once
		if (!isOverlapped) {
			//std::cout << "COLLISION::OVERLAP_BEGIN\n";
			isOverlapped = true;
		}
	}
	else if (isOverlapped) {
		//std::cout << "COLLISION::OVERLAP_END\n";
		isOverlapped = false;
	}
}

void Collision::resolution() {

}