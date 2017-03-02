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
#include "../include/meshInfo.h"

class Mesh
{
    public:
        Mesh();//constructor
        void LoadObjModel(const char *filename);//function to load obj model
        std::vector<MeshVert> returnMeshVert();//return vertices of mesh data
        std::vector<MeshVertTex> returnMeshVertTex();//return vertices, texture of mesh data
        std::vector<MeshVertTexNorm> returnMeshVertTexNorm();//return vertices, texture, normal of mesh data
    private:
        std::vector<glm::vec3> vertices;//to store vertex information of 3D model started with v
        std::vector<glm::vec2> texture;//to store texture co-ordinates
        std::vector<glm::vec3> normal;//to store normal co-ordinates
        std::vector<vertIndex> vertInd;//to store vertex only index
        std::vector<vertTexIndex> vertTexInd;//to store vertex and texture only index
        std::vector<vertTexNormIndex> vertTexNormInd;//to store vertex, texture and normal index

        std::vector<MeshVert> meshVert;//vertices only data
        std::vector<MeshVertTex> meshVertTex;//vertices and texture only data
        std::vector<MeshVertTexNorm> meshVertTexNorm;//vertices , texture and normal data

};

#endif // MESH_H
