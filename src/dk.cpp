#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shaders.h>
#include <stb_image.h>

#define WIDTH 800
#define HEIGHT 600

// shaders defines
#define VERTEX_FILE "./shaders/vertex.glsl"
#define FRAGMENT_FILE "./shaders/fragment.glsl"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "Resizing the window to " << width << "x" << height << ".\n";
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // debug variables
    int success;
    char infoLog[512];

    float vertices[] = {
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
//      0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f    // top center
        0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // top left
    };
    unsigned int indices[] = {
        // drawing a square
        0, 1, 3,
        0, 2, 3
        //
        // drawing a triangle
        //0, 1, 2
    };
    float texCoords[] = {
      0.0f, 0.0f, // bottom left corner
      1.0f, 0.0f, // bottom right corner
      0.5f, 1.0f  // top center corner
    };


    // GLFW: initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // creating a window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "mygame", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create glfw window" << std::endl;
        return -1;
    }

    // setting current context
    // fixes glad init error
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to init glad" << std::endl;
        return -1;
    }

    // setting a viewport and a resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);

    // binding the vao
    glBindVertexArray(vao);

    // element buffer objects
    unsigned int ebo;
    glGenBuffers(1, &ebo);

    // binding ebo to the GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // setting the vertex buffer object
    unsigned int vbo;
    glGenBuffers(1, &vbo);

    // binding vbo to GL_ARRAY_BUFFER (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // inserting data into GL_ARRAY_BUFFER (vbo)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //generating a texture
    unsigned int texture;
    glGenTextures(1, &texture);

    // binding the texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // setting the texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // loading an image to the program
    int width, height, nrChannels;
    unsigned char *data = stbi_load("images/wall.jpg", &width, &height, &nrChannels, 0);

    // error catching
    if (data) {
      // generating the image in the texture
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cerr << "Failed to load texture" << std::endl;
    }

    // freeing the image memory
    stbi_image_free(data);

    // shaders
    Shaders shaders(VERTEX_FILE, FRAGMENT_FILE);
    shaders.compileShaders();
    shaders.createProgram();

    // activating the shader program
    // glUseProgram(shaderProgram);

    // linking vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        // processing user keyboard input
        processInput(window);

        // setting window color
        glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        // instead of glUseProgram(shaderProgram);
        shaders.useProgram();

        // binding the texture
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
