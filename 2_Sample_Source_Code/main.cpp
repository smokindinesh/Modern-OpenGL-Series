#define GLEW_STATIC

// third-party libraries
#include <windows.h>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <cassert>
#include <iostream>
#include <stdexcept>

GLuint gVAO = 0;
GLuint gVBO = 0;
GLuint programId;
GLFWwindow* window = NULL;
GLFWmonitor* monitor = NULL;

const glm::vec2 SCREEN_SIZE(800, 600);

static void LoadTriangle() {

    // make and bind the VAO
   glGenVertexArrays(1, &gVAO);
   glBindVertexArray(gVAO);
   // make and bind the VBO
   glGenBuffers(1, &gVBO);
   glBindBuffer(GL_ARRAY_BUFFER, gVBO);
   // Put the three triangle verticies into the VBO

    GLfloat vertexData[] = {
        //  X     Y     Z
        0.0f, 0.8f, 0.0f,
       -0.8f,-0.8f, 0.0f,
        0.8f,-0.8f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

// draws a single frame
static void Render() {

    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT);
  // bind the VAO (the triangle)
    glBindVertexArray(gVAO);
   // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);
   // unbind the VAO
    glBindVertexArray(0);
    // swap the display buffers (displays what was just drawn)
   glfwSwapBuffers(window);

}
// the program starts here

void AppMain() {

    if(!glfwInit())
    throw std::runtime_error("glfwInit failed");
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "test window",NULL, NULL);
    if(!window)
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.2?");

    // GLFW settings
    glfwMakeContextCurrent(window);
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    // print out some info about the graphics drivers

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_4_2)
        throw std::runtime_error("OpenGL 4.2 API is not available.");

    // create buffer and fill it with the points of the triangle

    LoadTriangle();
    // run while the window is open

    while(glfwGetWindowAttrib(window,GLFW_FOCUSED)){
       // process pending events
        glfwPollEvents();
       // draw one frame
        Render();
    }
   // clean up and exit
   glfwTerminate();

}
int main(int argc, char *argv[]) {

    try {
        AppMain();

    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
