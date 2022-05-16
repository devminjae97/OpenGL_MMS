#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "shader.h"




//---------------------------
// <Dev setting & variables>
const bool isWireFrameModeOn = false;
const float clearColour[] = { 0.52f, 0.49f, 0.53f };

// Calculate fps, deltaTime
int frameCount = 0;
double currentTime = 0;
double lastTime = 0;
double lastTimeInFrame = 0;
double deltaTime;

// Input
bool isKey_Right_Pressed = false;
bool isKey_Left_Pressed = false;
bool isKey_Spacebar_Pressed = false;

// Variable for movement
bool isFacingRight = false;
bool isJumping = false;
glm::vec3 vec_walkUnit(0.0025f, 0, 0);

// Anim
double timeToChangeTexture = .57f;
double dt_anim = 0;
int index_animTex = 0;

enum AnimType{ANIM_IDLE = 0, ANIM_WALK, ANIM_JUMP};


//-----------------
// <Basic setting>
// Window
int window_width = 1024;
int window_height = 512;
const char* window_name = "MyMapleStory";
//const char* image_path = "Resources/testChar.png";

// MainCharacter
float mainCharacter_width_ratio;
float mainCharacter_height_ratio;
// ¦¦> Texture
int numOfSprites;

std::vector<unsigned int> vector_textureCurrent;
std::vector<unsigned int> vector_textureIdle;
std::vector<unsigned int> vector_textureWalk;
std::vector<unsigned int> vector_textureJump;
// ¦¦> Status
int mainCharacter_speed = 160;
float mainCharacter_jumpPower;


// Shaders
const char* vertexShaderSrc =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColour;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 myColour;\n"
"out vec2 texCoord;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"   gl_Position = model * vec4(aPos, 1.0);\n"
"   myColour = aColour;\n"
"   texCoord = aTexCoord;\n"
"}\n\0";

const char* fragmentShaderSrc =
"#version 330 core\n"
"out vec4 FragColour;\n"
"in vec3 myColour;\n"
"in vec2 texCoord;\n"
"uniform sampler2D myTexture;\n"
"void main()\n"
"{\n"
//"   FragColour = vec4(myColour, 1.0f);\n"
"   vec4 texColour = texture(myTexture, texCoord);\n"

"   if(texColour.a < 0.1f)\n"
"       discard;\n"                 // make transparency if colour.a value < 0.1f

"   FragColour = texColour;\n"
"}\n\0";






// --test--
// mat in loop[step-T]
glm::mat4 idMat4(1.0f);
glm::mat4 trans(1.0f);
glm::mat4 matTranslate(1.0f);
glm::mat4 matScale(1.0f);



//------------
// <Function>
void SetMainCharacterSize();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void calculateFPS();

// Input
void processInput(GLFWwindow* window);

// Movement
// m ¿ÖÇÊ¿ä?
void testMove(GLFWwindow* window, glm::mat4 m);
void testFaceRight(bool b);

// Texture Anim
void PlayAnim();
void SetAnim(AnimType aName);