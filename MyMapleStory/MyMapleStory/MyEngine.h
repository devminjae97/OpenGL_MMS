#pragma once

#include "global.h"
#include "shader.h"

#include "entity.h"
#include "maincharacter.h"
#include "structure.h"
#include "mob.h"


/*
* Does Setting variable need to move to global.h ? (= World Setting file)
* 
*/



//---------------------------
// <Dev setting & variables>
const bool isWireFrameModeOn = false;
const float clearColour[] = { 0.52f, 0.49f, 0.53f };
const bool isHideCollision = false;

const int MS_PER_UPDATE = 16;	// about 60 fps


//-----------------------------
// <Basic setting & variables>
const char* window_name = "MMS";

GLFWwindow* window;
int window_width = 1024;
int window_height = 768;



//-------------------
// <Manage Entities>
std::vector<Entity*> entities;




//------------
// <Function>
void Initialise();
void GenerateEntities();
void GameLoop();





//------------
// <Callback>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);