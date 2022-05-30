#include "MyEngine.h"


// Dev Note
/*****
 *
 * # OpenGL�� MapleStory ���� #
 *
 *
 * ########################
 * ##### TEST VERSION #####
 * ########################
 *
 *
 * ����) https://heinleinsgame.tistory.com/3?category=757483
 *
 */

int main() {

    //---------------
    // <Init window>
    glfwInit(); // Initialise
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // glfw'3'.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // glfw3.'3'
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create Window Object
    window = glfwCreateWindow(window_width, window_height, window_name, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Call this function to adjust Viewport when user adjust Window size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialise GLAD 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialise GLAD.\n";
        return -1;
    }



    //----------------
    // <Init & Load variables>
    Initialise();
    GenerateEntities();











    // wireframe mode
    if (isWireFrameModeOn)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // Rendering Loop (Frame)
    std::cout << ">> Begin Rendering Loop\n";

    while (!glfwWindowShouldClose(window)) {    // Check if the window was closed

        // Input
        //processInput(window);
        //testMove(window, trans);


        // --Rendering Codes--
        // Clear the screen
        glClearColor(clearColour[0], clearColour[1], clearColour[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);




        for (Entity* e : entities) {
            e->Activate(delta_time);
        }




        // Detect collision 




        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Calculate FPS
        Clock();
    }


    // Terminate all resources
    glfwTerminate();









    std::cout << "Terminate Program\n";


    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Initialise() {
    //------------------
    // Global variables
    Global::window = window;
    Global::window_width = window_width;
    Global::window_height = window_height;

    Global::isHideCollision = isHideCollision;

    //-----------------
    // Local variables
    delta_time = 0;

}

void GenerateEntities() {

    // MainCharacter
    MainCharacter* main_character = new MainCharacter();
    entities.push_back(main_character);

}

void Clock() {

    current_time = glfwGetTime();

    frame_count++;

    double interval = current_time - last_time;
    delta_time = current_time - last_time_in_frame;

    // Update fps per 1 second
    if (interval > 1) {
        std::string buf = window_name + std::string(" | ") + std::to_string((int)(frame_count / interval)) + std::string(" fps");

        glfwSetWindowTitle(window, buf.c_str());

        frame_count = 0;
        last_time = current_time;
    }

    last_time_in_frame = current_time;
}