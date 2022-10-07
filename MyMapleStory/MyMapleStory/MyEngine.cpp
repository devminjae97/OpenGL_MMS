#include "MyEngine.h"


// Dev Note
/*****
 *
 * # MapleStory with OpenGL#
 *
 *
 * ########################
 * ##### TEST VERSION #####
 * ########################
 *
 *
 * Conference) https://heinleinsgame.tistory.com/3?category=757483
 *
 * 
 * to be modified
 * Global => WorldSetting
 * Activate => Update
 * Seperate Update and Render 
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

    glViewport(0, 0, window_width, window_height);

    //----------------
    // <Init & Load variables>
    Initialise();
    GenerateEntities();

    // wireframe mode
    if (isWireFrameModeOn)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    GameLoop();


    // Terminate all resources
    glfwTerminate();

    for (Entity* e : entities) {
        delete e;
    }

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
}

void GenerateEntities() {

    // test
    //-------------
    // <Structure>
    Structure* test_structure = new Structure(64, 64, "white");
    test_structure->SetPosition(256, 16);
    test_structure->SetColliderBlockMode(true);
    entities.push_back(test_structure);

    test_structure = new Structure(64, 64, "white");
    test_structure->SetPosition(192, -64);
    test_structure->SetColliderBlockMode(true);
    entities.push_back(test_structure);

    test_structure = new Structure(1024, 128, "white");
    test_structure->SetPosition(0, -128 - 32);
    test_structure->SetColliderBlockMode(true);
    entities.push_back(test_structure);


    // <Mob>
    Mob* test_mob = new Mob(128, 128, "OrangeMushroom", false);
    test_mob->SetPosition(-128, -62);
    entities.push_back(test_mob);

    // <MainCharacter>
    MainCharacter* main_character = new MainCharacter();
    entities.push_back(main_character);
}

void GameLoop() {
    double prev_time = glfwGetTime();
    double elapsed = 0.0;
    int frame_count = 0;

    // Update & Rendering Loop (Frame)
    while (!glfwWindowShouldClose(window)) {    // Check if the window was closed

        //------------------
        // <Calculate time>
        double current_time = glfwGetTime();
        double delta_time = current_time - prev_time;
        prev_time = current_time;

        // Calculate FPS
        elapsed += delta_time;
        frame_count += 1;
        if (elapsed >= 1.0) {
            std::string buf = window_name + std::string(" | ") + std::to_string((int)(frame_count / elapsed)) + std::string(" fps");

            glfwSetWindowTitle(window, buf.c_str());

            elapsed = 0;
            frame_count = 0;
        }



        //------------------
        // <Process Input>
        //processInput(window);
        



        //------------------
        // <Fixed Update>
        for (Entity* e : entities) {
            e->Update(delta_time);
        }


        //-------------------
        // <Render>

        // Clear the screen
        glClearColor(clearColour[0], clearColour[1], clearColour[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        for (Entity* e : entities) {
            e->Render(delta_time);
        }

        //main_character->collision->checkCollision(test_structure->collision);


        // Detect collision 
        // tmp code



        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
