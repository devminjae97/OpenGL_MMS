#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Collision {

private:
	// need to initialize in collision manager or wherever.
	static unsigned int count;

	int id;

	bool isBlockMode;

	// type�߰��ϱ�; main character, monster, land(map), portal, ...

	float x;
	float y;

	// Actually, half of real width or height value
	float width;
	float height;

	bool isOverlapped = false;	// �ϳ��ۿ� ������
	
public:
	Collision(glm::mat4 tr, float w, float h);
	Collision(glm::mat4 tr, float w, float h, bool b);

	void setBlockMode(bool b);
	void setTrans(glm::mat4 tr);
	
	void checkCollision(Collision c);
	void resolution();
		

};