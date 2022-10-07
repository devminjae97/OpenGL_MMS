#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define	ERROR	-9999
#define	NONE	-1000


class Global {
public:

	//--------------------
	// <Window variables>
	static GLFWwindow* window;

	static int window_width;
	static int window_height;

	//---------------
	// <Dev Setting>
	static bool isHideCollision;
	static bool is_paused;

};