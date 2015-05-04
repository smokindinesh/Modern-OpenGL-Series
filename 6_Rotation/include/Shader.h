#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include<GL/glew.h>
#include<iostream>
#include<fstream>
#include <stdexcept>
class Shader
{
    public:
        Shader();
        GLuint LoadShader(const char *shaderFile, GLenum type);

        GLuint ReturnShaderID();
        virtual ~Shader();
    private:
        GLuint shaderID;
};

#endif // SHADER_H
