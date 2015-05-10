#ifndef PROGRAM_H
#define PROGRAM_H

#define GLEW_STATIC
#include <stdexcept>
#include<vector>
#include<GL/glew.h>

class Program
{
    public:
        Program(const std::vector<GLuint> shaders);
        virtual ~Program();
        GLuint ReturnProgramID() const;
        GLint attrib(const GLchar* attribName) const;
        GLint uniform(const GLchar* uniformName) const;
    private:
        GLuint programID;
        //copying disabled
        //Program(const Program&);

};

#endif // PROGRAM_H
