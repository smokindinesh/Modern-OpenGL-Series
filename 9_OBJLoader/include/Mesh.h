#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <GL/glew.h>

class Mesh
{
    public:
        Mesh();//constructor
        void LoadObjModel(const char *filename);//function to load obj model
        std::vector<glm::vec3> returnMesh();//return the vertices of mesh data
    private:
        std::vector<glm::vec3> vertices;//to store vertex information of 3D model started with v
        std::vector<glm::vec3> meshVertices;//to store all 3D model face vertices
        std::vector<int> faceIndex;//to store the number of face index started with f

};

#endif // MESH_H
