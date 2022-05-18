// MyMapleStory.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "MyMapleStory.h"


// Dev Note
/*****
 * 
 * # OpenGL로 MapleStory 구현 #
 * 
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


    /*
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
    */


    //test shaders
    Shader mShader("Shaders/characterShader.vs", "Shaders/characterShader.fs");

    Shader oShader("Shaders/objectShader.vs", "Shaders/objectShader.fs");



    // --------------
    // Get ready main character

    SetMainCharacterSize();

    float vertices[] = {
        mainCharacter_width_ratio, mainCharacter_height_ratio, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,     // RT
        mainCharacter_width_ratio, -mainCharacter_height_ratio, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,     // RB
        -mainCharacter_width_ratio, -mainCharacter_height_ratio, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // LB
        -mainCharacter_width_ratio, mainCharacter_height_ratio, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // LT
    };  // range >> position: -1 ~ 1/ colour: 0 ~ 1/ texture coord: 0 ~ 1

    unsigned int indices[] = {
        0, 1, 3,    // 1st triangle
        1, 2, 3     // 2nd triangle
    };

    // Vertex Buffer Object, Vertex Array Object, Element Buffer Object
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
    



    // Test Object
    float oVertices[] = {
        mainCharacter_width_ratio/2, mainCharacter_height_ratio/2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,     // RT
        mainCharacter_width_ratio/2, -mainCharacter_height_ratio/2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,     // RB
        -mainCharacter_width_ratio/2, -mainCharacter_height_ratio/2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // LB
        -mainCharacter_width_ratio/2, mainCharacter_height_ratio/2, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // LT
    };  // range >> position: -1 ~ 1/ colour: 0 ~ 1/ texture coord: 0 ~ 1

    unsigned int oIndices[] = {
        0, 1, 3,    // 1st triangle
        1, 2, 3     // 2nd triangle
    };

    glm::mat4 oTrans(1.0f);
    oTrans = glm::translate(oTrans, glm::vec3(mainCharacter_height_ratio,-mainCharacter_height_ratio / 2,0.f));

    // Vertex Buffer Object, Vertex Array Object, Element Buffer Object
    unsigned  int oVBO, oVAO, oEBO;

    glGenBuffers(1, &oVBO);
    glGenBuffers(1, &oEBO);
    glGenVertexArrays(1, &oVAO);
    glBindVertexArray(oVAO);

    glBindBuffer(GL_ARRAY_BUFFER, oVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(oVertices), oVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(oIndices), oIndices, GL_STATIC_DRAW); 

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    

    // Test Character collision
    float cf_width = mainCharacter_width_ratio * 0.25f;
    float cf_height = mainCharacter_height_ratio * 0.5f;

    float cfVertices[] = {
        cf_width, cf_height, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,     // RT
        cf_width, -cf_height, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,     // RB
        -cf_width, -cf_height, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // LB
        -cf_width, cf_height, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // LT
    };  // range >> position: -1 ~ 1/ colour: 0 ~ 1/ texture coord: 0 ~ 1

    unsigned int cfIndices[] = {
        0, 1, 3,    // 1st triangle
        1, 2, 3     // 2nd triangle
    };

    glm::vec3 cfOffset(0.0f,-mainCharacter_height_ratio * 0.5f, 0.f);

    // Vertex Buffer Object, Vertex Array Object, Element Buffer Object
    unsigned  int cfVBO, cfVAO, cfEBO;

    glGenBuffers(1, &cfVBO);
    glGenBuffers(1, &cfEBO);
    glGenVertexArrays(1, &cfVAO);
    glBindVertexArray(cfVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cfVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cfVertices), cfVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cfEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cfIndices), cfIndices, GL_STATIC_DRAW); 

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);







    //-----------
    // <Texture>
    //unsigned int texture;
    int texture_width, texture_height, nrChannels;

    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    // Idle : 3(+1) sprites
    for (int i = 0; i < 3; i++) {
        unsigned int tmpTex;
        glGenTextures(1, &tmpTex);
        glBindTexture(GL_TEXTURE_2D, tmpTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        std::string folder_path = "Resources/avatar/avatar_idle_" + std::to_string(i + 1) + ".png";

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

        vector_textureIdle.push_back(tmpTex);
    }
    vector_textureIdle.push_back(vector_textureIdle[1]);


    // Walk : 4 sprites
    for (int i = 0; i < 4; i++) {
        unsigned int tmpTex;
        glGenTextures(1, &tmpTex);
        glBindTexture(GL_TEXTURE_2D, tmpTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        std::string folder_path = "Resources/avatar/avatar_walk_" + std::to_string(i + 1) + ".png";

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

        vector_textureWalk.push_back(tmpTex);
    }


    // test object
    unsigned int oTex;
    glGenTextures(1, &oTex);
    glBindTexture(GL_TEXTURE_2D, oTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::string object_path = "Resources/test/collision.png";

    unsigned char* oData = stbi_load(object_path.c_str(), &texture_width, &texture_height, &nrChannels, 0);

    if (oData) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set pixel store mode
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, oData);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(oData);
    }
    else {
        std::cout << "ERROR::TEXTURE::LOADING_FALIED\n--path: " << object_path << "\n";
    }








    
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



    // init Texture
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, vector_textureIdle[0]);
    SetAnim(ANIM_IDLE);

    glBindVertexArray(oVAO);
    glBindTexture(GL_TEXTURE_2D, oTex);



    // Rendering Loop (Frame)
    while (!glfwWindowShouldClose(window)) {    // Check if the window was closed

        // Input
        processInput(window);
        testMove(window, trans);


        // --Rendering Codes--
        // Clear the screen
        glClearColor(clearColour[0], clearColour[1], clearColour[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Test collision
        oShader.use();
        oShader.setMat4("model", oTrans);
        glBindVertexArray(oVAO);
        glBindTexture(GL_TEXTURE_2D, oTex);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // Main character
        mShader.use();
        mShader.setMat4("model", trans);
        glBindVertexArray(VAO); 
        PlayAnim();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // 6 vertices (2 triangles), 0 offset

        // Main character collider
        oShader.use();

        glm::mat4 cfTrans = glm::translate(trans, cfOffset);
        // ->>>> 중심???
        oShader.setMat4("model", cfTrans);
        glBindVertexArray(cfVAO);
        glBindTexture(GL_TEXTURE_2D, oTex);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        

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
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !isKey_Left_Pressed) {
        if (!isKey_Right_Pressed) {
            isKey_Right_Pressed = true;
            testFaceRight(true);

            if(!isJumping)
                SetAnim(ANIM_WALK);
        }

        matTranslate = glm::translate(matTranslate, vec_walkUnit * (float)(deltaTime * mainCharacter_speed));
        trans = matTranslate * matScale;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && isKey_Right_Pressed) {
        isKey_Right_Pressed = false;

        if (!isJumping)
            SetAnim(ANIM_IDLE);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !isKey_Right_Pressed) {
        if (!isKey_Left_Pressed) {
            isKey_Left_Pressed = true;
            testFaceRight(false);

            if (!isJumping)
                SetAnim(ANIM_WALK);
        }

        matTranslate = glm::translate(matTranslate, vec_walkUnit * (float)(deltaTime * -mainCharacter_speed));
        trans = matTranslate * matScale;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE && isKey_Left_Pressed) {
        isKey_Left_Pressed = false;

        if (!isJumping)
            SetAnim(ANIM_IDLE);
    }
}

void testFaceRight(bool b){
    if (!isFacingRight && b) {
        isFacingRight = true;
        matScale = glm::scale(glm::mat4(1.f), glm::vec3(-1.f, 1.f, 1.f));
    }
    else if (isFacingRight && !b) {
        isFacingRight = false;
        matScale = glm::mat4(1.f);
    }
}


void PlayAnim() {
    dt_anim += deltaTime;

    if (dt_anim > timeToChangeTexture) {
        dt_anim = 0;
        index_animTex == (numOfSprites - 1) ? index_animTex = 0 : index_animTex++;
    }
    glBindTexture(GL_TEXTURE_2D, vector_textureCurrent[index_animTex]);
}

void SetAnim(AnimType aType) {
    switch (aType)
    {
    case ANIM_IDLE:
        vector_textureCurrent = vector_textureIdle;
        timeToChangeTexture = 0.57f;
        break;
    case ANIM_WALK:
        vector_textureCurrent = vector_textureWalk;
        timeToChangeTexture = -0.001875 * mainCharacter_speed + 0.45f;  // 160->0.15f, 80->0.3f
        break;
    case ANIM_JUMP:
        break;
    default:
        break;
    }


    numOfSprites = vector_textureCurrent.size();
    dt_anim = 0;
    index_animTex = 0;

    glBindTexture(GL_TEXTURE_2D, vector_textureCurrent[0]);
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
