#pragma once

#include "global.h"
#include "shader.h"

#include "entity.h"
#include "maincharacter.h"
#include "structure.h"






//---------------------------
// <Dev setting & variables>
const bool isWireFrameModeOn = false;
const float clearColour[] = { 0.52f, 0.49f, 0.53f };
const bool isHideCollision = false;


//-----------------------------
// <Basic setting & variables>
const char* window_name = "MMS";

GLFWwindow* window;
int window_width = 1024;
int window_height = 768;



//--------------------------
// <Clock; fps, delta time>
int frame_count = 0;
double current_time = 0;
double last_time = 0;
double last_time_in_frame = 0;
double delta_time;

void Clock();


//-------------------
// <Manage Entities>
std::vector<Entity*> entities;




//------------
// <Function>
void Initialise();
void GenerateEntities();





//------------
// <Callback>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);