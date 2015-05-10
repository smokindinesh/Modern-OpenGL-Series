#define GLEW_STATIC
// third-party libraries
#include <windows.h>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

// program classes
#include "include/Program.h"
#include"include/Shader.h"
// screen size
glm::vec2 SCREEN_SIZE(800, 600);

// globals
Program* program = NULL;
Shader shader;
GLuint gVAO = 0;
GLuint gVBO = 0;
GLfloat rotationAngle=0;
GLFWwindow* MainWindow = NULL;
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix

//Called when a key is pressed
void handleKeypress(GLFWwindow* window,int key,int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//The key that was pressed
        exit(0);
}

//Called when the window is resized
void handleResize(GLFWwindow* window,int width,int height)
{
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport( 0, 0, width, height );
    SCREEN_SIZE= glm::vec2(width,height);


    glMatrixMode( GL_PROJECTION ); //Switch to setting the camera perspective
    //Set the camera perspective
    glLoadIdentity(); //reset the camera
                         //The far z clipping coordinate
}
// update the scene based on the time elapsed since last update
void Update(float secondsElapsed) {
    const GLfloat degreesPerSecond = 1.0f;
    rotationAngle += secondsElapsed * degreesPerSecond;
    while(rotationAngle > 360.0f) rotationAngle -= 360.0f;
}
// loads the vertex shader and fragment shader, and links them to make the global program
static void LoadShaders() {
    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("vertex.glsl", GL_VERTEX_SHADER));
    shaders.push_back(shader.LoadShader("fragment.glsl", GL_FRAGMENT_SHADER));
    program = new Program(shaders);
}


// loads a triangle into the VAO global
static void LoadTriangle() {
    // make and bind the VAO
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    // Put the three triangle verticies into the VBO
    GLfloat vertexData[] = {
        //  X     Y     Z   R    G     B    A
         0.0f, 0.8f, 0.0f,1.0f,0.0f,0.0f,1.0f,
        -0.8f,-0.8f, 0.0f,0.0f,1.0f,0.0f,1.0f,
         0.8f,-0.8f, 0.0f,0.0f,0.0f,1.0f,1.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    // connect the xyz to the "vPosition" attribute of the vertex shader
    glEnableVertexAttribArray(program->attrib("vPosition"));
    glVertexAttribPointer(program->attrib("vPosition"), 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), NULL);
    // connect the RGBA to the "vColor" attribute of the vertex shader and passed to the fragment shader
    glVertexAttribPointer(program->attrib("vColor"), 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat),(const GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(program->attrib("vColor"));


    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// draws a single frame
static void Render(GLFWwindow* window) {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT);

    // bind the program (the shaders)
    glUseProgram(program->ReturnProgramID());

    // Projection matrix : 45° Field of View, aspect ratio, display range : 1 unit <-> 200 units
    projectionMatrix = glm::perspective(45.0f, (float)SCREEN_SIZE.x / (float)SCREEN_SIZE.y, 1.0f, 200.0f);
    glUniformMatrix4fv(program->uniform("prespective"),1,GL_FALSE,glm::value_ptr(projectionMatrix));
    // Camera matrix
    viewMatrix = glm::lookAt(
                 glm::vec3(0,0,1), // Camera is at (4,3,3), in World Space
                 glm::vec3(0,0,0), // and looks at the origin
                 glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                 );

    glUniformMatrix4fv(program->uniform("camera"),1,GL_FALSE,glm::value_ptr(viewMatrix));
    // Model matrix : an identity matrix (model will be at the origin)
    modelMatrix= glm::mat4(1.0f);// Changes for each model !
    modelMatrix= glm::translate(modelMatrix,glm::vec3(0,0,-5));//translating to negative z-axis
    modelMatrix= glm::scale(modelMatrix,glm::vec3(2,2,2));//scalling by 2x
    modelMatrix= glm::rotate(modelMatrix, -rotationAngle, glm::vec3(0,0,1));//rotating in clockwise direction

    glUniformMatrix4fv(program->uniform("model"),1,GL_FALSE,glm::value_ptr(modelMatrix));

    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);

    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // unbind the VAO
    glBindVertexArray(0);

    // unbind the program
    glUseProgram(0);

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers(window);
}


// the program starts here
void MainApplication() {
    // initialise GLFW
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    MainWindow = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y,"Color",NULL,NULL);
    if(!MainWindow)
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.2?");

    glfwSetWindowSizeCallback(MainWindow,handleResize); //callback function of GLFW to handle window resize
    glfwSetKeyCallback(MainWindow,handleKeypress); //callback function to handle keypress

    glfwMakeContextCurrent(MainWindow);

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

    // load vertex and fragment shaders into opengl
    LoadShaders();

    // create buffer and fill it with the points of the triangle
    LoadTriangle();

    // run while the window is open
    double lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(MainWindow)){
        // update the scene based on the time elapsed since last update
        double thisTime = glfwGetTime();
        Update(thisTime - lastTime);
        lastTime = thisTime;

        // process pending events
        glfwPollEvents();

        // draw one frame
        Render(MainWindow);


    }

    // clean up and exit
    glfwTerminate();
}


int main(int argc, char *argv[]) {
    try {
        MainApplication();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
