#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>

#include "build_config.h"

// Part  of GLFW context
void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

int main(void) 
{
    // Start GLFW context
    if (!glfwInit())
        return 1; // Failed to initialize

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(640, 480, PROJECT_NAME, NULL, NULL);
    if (!window)
        return 1; // Failed to create window or OpenGL context

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    while (!glfwWindowShouldClose(window))
    {
        // Keep running
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    // End GLFW context

    return 0;
}