#define GLEW_STATIC
// third-party libraries
#include <windows.h>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <iostream>

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

GLuint gVAO = 0;
GLuint gVBO = 0;
GLuint programId;
GLFWwindow* MainWindow = NULL;
glm::vec2 SCREEN_SIZE(800, 600);

glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix

//Called when a key is pressed
void handleKeypress(GLFWwindow* window,int key,int scancode, int action, int mods) //The key that was pressed
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
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



GLuint loadShader(char *shaderFile, GLenum type)
{
    std::ifstream in(shaderFile);
    std::string src= "";
    std::string line="";
    while(std::getline(in,line))
    src += line + "\n";
    std::cout << src;
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);

    const char* source = src.c_str();
    glShaderSource(shader,1,&source,NULL);
    glCompileShader(shader);
    if(!shader)
    {
        std::cerr << "Could not compile the shader";
        return 0;
    }
    return shader;
}
GLuint createShaderProgram()
{
    GLuint vertexShader,fragmentShader;
    GLint linked;

    vertexShader = loadShader("vertex.glsl",GL_VERTEX_SHADER);
    fragmentShader = loadShader("fragment.glsl",GL_FRAGMENT_SHADER);
    if(!vertexShader || !fragmentShader) return 0;

    programId=glCreateProgram();
    if(!programId)
    {
        std::cerr << "could not create the shader program";
        return 0;

    }
    glAttachShader(programId,vertexShader);
    glAttachShader(programId,fragmentShader);

    glBindAttribLocation(programId,0,"vPosition");
    glLinkProgram(programId);
    glGetProgramiv(programId,GL_LINK_STATUS,&linked);
    if(!linked)
    {
        std::cerr << "could not link the shader";
        return 0;
    }
    glUseProgram(programId);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projectionMatrix = glm::perspective(45.0f, (float)SCREEN_SIZE.x / (float)SCREEN_SIZE.y, 0.1f, 100.0f);
    // Camera matrix
    viewMatrix       = glm::lookAt(
    glm::vec3(0,0,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    modelMatrix      = glm::mat4(1.0f);  // Changes for each model !
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = projectionMatrix * viewMatrix * modelMatrix; // Remember, matrix multiplication is the other way around
    // Get a handle for our "MVP" uniform.
    // Only at initialisation time.
    GLuint MatrixID = glGetUniformLocation(programId, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


 return programId;
}

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

        //Pentagon
        0.5f, 0.5f, -5.0f,
        1.5f, 0.5f, -5.0f,
        0.5f, 1.0f, -5.0f,

        0.5f, 1.0f, -5.0f,
        1.5f, 0.5f, -5.0f,
        1.5f, 1.0f, -5.0f,

        0.5f, 1.0f, -5.0f,
        1.5f, 1.0f, -5.0f,
        1.0f, 1.5f, -5.0f,

        //Triangle
        -0.5f, 0.5f, -5.0f,
        -1.0f, 1.5f, -5.0f,
        -1.5f, 0.5f, -5.0f,
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
static void Render(GLFWwindow* window) {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT);

    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);

    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 12);

    // unbind the VAO
    glBindVertexArray(0);

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers(window);
}

// the program starts here
void MainAppFunc() {
    // initialise GLFW
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    MainWindow = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y,"Perspective Projection",NULL,NULL);
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
    //LoadShaders();
   if(!createShaderProgram())
   {
       std::cerr << "Could not create the shaders";
   }

    // create buffer and fill it with the points of the triangle
    LoadTriangle();

    // run while the window is open
    while(!glfwWindowShouldClose(MainWindow)){

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
        MainAppFunc();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

