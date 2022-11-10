// ref: https://learnopengl.com/Getting-started/Hello-Triangle
// #define GLAD_GL_IMPLEMENTATION
// #include <glad/gl.h>
#include "glwrapper.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "build_config.h"
#include "shader.h"
#include "matrix.h"
#include "quaternion.h"

// Part  of GLFW context
void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

// Part  of GLFW context
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main(void) 
{
    // init
    if (!glfwInit())
        return 1; // Failed to initialize

    // configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, PROJECT_NAME, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1; // Failed to create window or OpenGL context
    }
    glfwMakeContextCurrent(window);

    // define callback
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD load all OpenGL function pointers
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    glfwSwapInterval(1);

    // Build and compile shader program
    // --------------------------------
    boids::Shader* shader = new boids::Shader("source/core/shaders/simple-shaders/vertex.glsl", "source/core/shaders/simple-shaders/fragment.glsl"); // TODO fix path

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.25f, -0.5f, 0.0f, // bottom left
        0.0f, -0.35f, 0.0f,  // bottom mid
        0.25f, -0.5f, 0.0f,  // bottom right
        0.0f, 0.5f, 0.0f    // top mid
    };
    GLuint indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // Vertex array object
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array); // MUst bind before the vertex buffer(s) and then configure vertex attribute(s).

    // Buffer
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Box Buffer
    GLuint box_buffer;
    glGenBuffers(1, &box_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // linking vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // don't unbind while a VAO is active

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // TODO check OpenGL error

    /*--------------------------*/
    // context

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float scale = 0.0f;
    float delta = 0.0001f;

    while (!glfwWindowShouldClose(window))
    {
        // Event loop

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformation
        scale += delta;
        if (scale >= 1.0f || scale <= -1.0f)
            delta *= -1;

        mat4 transform = mat4::indentity();
        float translation[] = {0.0, (float)(scale*1/0.2), 0.0};
        float axis[] = {0.0f, 0.0f, 1.0f};
        transform.scale(0.2);
        transform.rotate(0.785, axis);
        // transform.rotate((float)glfwGetTime(), axis);
        transform.translate(translation);

        // rendering after this call will use program (shaders)
        shader->use();
        shader->set_mat_4("transform", transform.value_ptr());
        
        // Draw stuff
        glBindVertexArray(vertex_array); // bind the vertex array to draw its object
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //  end context
    /*--------------------------*/

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &box_buffer);
    delete shader; // must call glDeleteProgram before destroying the window

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}