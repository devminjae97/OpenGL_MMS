﻿// MyMapleStory.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "MyMapleStory.h"


// Dev Note
/*****
 * 
 * # OpenGL로 MapleStory 구현 #
 * 
 * 
 * 
 * 
 * 220510 - 사각형 띄움(texture 미포함)
 * 220511 - 캐릭터 texture 추가
 * 220513 - fps, deltaTime, 단순 좌우이동 기능 추가 (함수 정리 필요)
 * 
 * ----------------
 * 
 * 중단점:
 * 2-5::Uniform << 공부해야함
 * 2-7::transform (translate 위주일듯)
 * 
 * 
 * 참고) https://heinleinsgame.tistory.com/3?category=757483
 * 기타) Change booting logo:https://gall.dcinside.com/mgallery/board/view/?id=laptop&no=588941
 * 
 */


int main() {


    glfwInit(); // Initialise
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // glfw'3'.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // glfw3.'3'
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  

    // Create Window Object
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_name, NULL, NULL);

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


    // Set ViewPort
    //glViewport(0, 0, window_width, window_height); // (left, bottom, right, top)



    // --Compile shader programme--
    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);    // Create shader
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    // Check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
    }
    // Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
    }
    // Link Shaders
    unsigned int shaderProgramme;
    shaderProgramme = glCreateProgram();
    glAttachShader(shaderProgramme, vertexShader);
    glAttachShader(shaderProgramme, fragmentShader);
    glLinkProgram(shaderProgramme);
    // Check for linking errors
    glGetProgramiv(shaderProgramme, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramme, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAMME::LINKING_FAILED\n" << infoLog << "\n";
    }

    // We Don't need these shader objects anymore.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);





    // --------------
    // Get ready main character

    SetMainCharacterSize();

    float vertices[] = {
        mainCharacter_width_ratio, mainCharacter_height_ratio, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,     // RT
        mainCharacter_width_ratio, -mainCharacter_height_ratio, 0.0f, .0f, 1.0f, 0.0f, 1.0f, 0.0f,     // RB
        -mainCharacter_width_ratio, -mainCharacter_height_ratio, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // LB
        -mainCharacter_width_ratio, mainCharacter_height_ratio, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // LT
    };  // range >> position: -1 ~ 1/ colour: 0 ~ 1/ texture coord: 0 ~ 1

    unsigned int indices[] = {
        0, 1, 3,    // 1st triangle
        1, 2, 3     // 2nd triangle
    };



    // Vertex Buffer Object, Element Buffer Object, Vertex Array Object
    unsigned  int VBO, VAO, EBO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);




    // --Texture--
    unsigned int texture, texture2;
    std::vector<unsigned int> vec_textureIdle;
    int texture_width, texture_height, nrChannels;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //test - idle texture ; 3 sprites
    for (int i = 0; i < 3; i++) {
        unsigned int tmpTex;
        glGenTextures(1, &tmpTex);
        glBindTexture(GL_TEXTURE_2D, tmpTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        std::string folder_path = "Resources/avatar/avatar_idle_" + std::to_string(i+1) + ".png";


        unsigned char* tmpData = stbi_load(folder_path.c_str(), &texture_width, &texture_height, &nrChannels, 0);

        if (tmpData) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set pixel store mode
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmpData);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(tmpData);
        }
        else {
            std::cout << "ERROR::TEXTURE::LOADING_FALIED\n--path: " << folder_path << "\n";
        }

        vec_textureIdle.push_back(tmpTex);
    }
    vec_textureIdle.push_back(vec_textureIdle[1]);








    
    //stbi_set_flip_vertically_on_load(true);
    
    
    // For GL_CLAMP_TO_BORDER
    //float borderColour[] = { .0f, .0f, .0f, .0f };   // transparent maybe...?
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
    /*
    unsigned char* data = stbi_load(image_path, &texture_width, &texture_height, &nrChannels, 0);


    const char* test_path = "Resources/avatar/avatar_jump.png";
    unsigned char* testData = stbi_load(test_path, &texture_width, &texture_height, &nrChannels, 0);
    
    if (data && testData) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, testData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "!Can't find the Image!\n";
    }

    stbi_image_free(data);
    */









    // Bind Texture
    //glActiveTexture(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture);






    // wireframe mode
    if(isWireFrameModeOn)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //anim test
    double dt = 0;
    int ci = 0;
    glBindTexture(GL_TEXTURE_2D, vec_textureIdle[ci]);

    // Rendering Loop (Frame)
    while (!glfwWindowShouldClose(window)) {    // Check if the window was closed


        // Input
        processInput(window);
        testMove(window, trans);

        dt += deltaTime;
        if (dt > .57f) {
            dt = 0;
            ci += ci == 3 ? -3 : 1;
            glBindTexture(GL_TEXTURE_2D, vec_textureIdle[ci]);

            std::cout << "change img to idle_" << (ci + 1) << "\n";
        }


        // --Rendering Codes--
        // Clear the screen
        glClearColor(clearColour[0], clearColour[1], clearColour[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //// Bind Texture
        //glActiveTexture(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, texture2);

        // Draw Figure
        glUseProgram(shaderProgramme);


        // --transform--
        // Set model translate matrix
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramme, "model"), 1, GL_FALSE, glm::value_ptr(trans));






        
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);   // 3 vertices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // 6 vertices (2 triangles), 0 offset
        


        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    
        // Calculate FPS
        calculateFPS();
    }


    // Terminate all resources
    glfwTerminate();





    std::cout << "Hello World!\n";

    return 0;

}

void SetMainCharacterSize() {
    const int unit = 128;
    mainCharacter_width_ratio = (float)unit / window_width;
    mainCharacter_height_ratio = (float)unit / window_height;

    std::cout << mainCharacter_width_ratio << "/" << mainCharacter_height_ratio << "\n";
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void calculateFPS() {
    currentTime = glfwGetTime();

    frameCount++;

    double timeInterval = currentTime - lastTime;
    deltaTime = currentTime - lastTimeInFrame;
    
    // Print fps per 1 second
    if (timeInterval > 1) {
        std::cout << "fps: " << frameCount / timeInterval << "\n";

        frameCount = 0;
        lastTime = currentTime;
    }

    lastTimeInFrame = currentTime;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void testMove(GLFWwindow* window, glm::mat4 m) {

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (!isKey_Right_Pressed) {
            isKey_Right_Pressed = true;
            testFaceRight(true);
        }

        matTranslate = glm::translate(matTranslate, glm::vec3(1.f, 0.f, 0.f) * (float)deltaTime);
        trans = matTranslate * matScale;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && isKey_Right_Pressed) {
        isKey_Right_Pressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (!isKey_Left_Pressed) {
            isKey_Left_Pressed = true;
            testFaceRight(false);
        }

        matTranslate = glm::translate(matTranslate, glm::vec3(-1.f, 0.f, 0.f) * (float)deltaTime);
        trans = matTranslate * matScale;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE && isKey_Left_Pressed) {
        isKey_Left_Pressed = false;
    }
}

void testFaceRight(bool b)
{
    if (!isFacingRight && b) {
        isFacingRight = true;
        matScale = glm::scale(glm::mat4(1.f), glm::vec3(-1.f, 1.f, 1.f));
    }
    else if (isFacingRight && !b) {
        isFacingRight = false;
        matScale = glm::mat4(1.f);
    }
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.