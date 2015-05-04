#include "../include/Program.h"

Program::Program(const std::vector<GLuint> shaders) :
    programID(0)
{
    if(shaders.size() <= 0)
        throw std::runtime_error("No shaders were provided to create the program");

    //create the program object
    programID = glCreateProgram();
    if(programID == 0)
        throw std::runtime_error("glCreateProgram failed");

    //attach all the shaders
    for(unsigned i = 0; i < shaders.size(); ++i)
        glAttachShader(programID, shaders[i]);

    //link the shaders together
    glLinkProgram(programID);

    //detach all the shaders
    for(unsigned i = 0; i < shaders.size(); ++i)
        glDetachShader(programID, shaders[i]);

    //throw exception if linking failed
    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteProgram(programID); programID = 0;
        throw std::runtime_error(msg);
    }
}

Program::~Program()
{
    //dtor
}
GLuint Program::ReturnProgramID() const
{
    return programID;
}
GLint Program::attrib(const GLchar* attribName) const
{
    if(!attribName)
        throw std::runtime_error("attribName was NULL");

    GLint attrib = glGetAttribLocation(programID, attribName);
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);

    return attrib;
}

GLint Program::uniform(const GLchar* uniformName) const
{
    if(!uniformName)
        throw std::runtime_error("uniformName was NULL");

    GLint uniform = glGetUniformLocation(programID, uniformName);
    if(uniform == -1)
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);

    return uniform;
}
