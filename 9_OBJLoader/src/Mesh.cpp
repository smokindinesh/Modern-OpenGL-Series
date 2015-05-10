#include "../include/Mesh.h"

Mesh::Mesh()
{
    //ctor
}
void Mesh::LoadObjModel(const char *filename)
{
    std::ifstream in(filename, std::ios::in);
    if (!in)
        {
            std::cerr << "Cannot open " << filename << std::endl;
            exit(1);

        }
    std::string line;
    while (std::getline(in, line))
    {
      //cout<<line<<endl;
      if (line.substr(0,2)=="v "){
            std::istringstream v(line.substr(2));
            glm::vec3 vert;
            double x,y,z;
            v>>x;v>>y;v>>z;
            vert=glm::vec3(x,y,z);
            vertices.push_back(vert);
      }
      else if(line.substr(0,2)=="f "){
        std::istringstream v(line.substr(2));
        GLuint a,b,c;
        v>>a;v>>b;v>>c;
        a--;b--;c--;
        faceIndex.push_back(a);
        faceIndex.push_back(b);
        faceIndex.push_back(c);
      }

    }
    for(unsigned int i=0;i<faceIndex.size();i++)
    {
        glm::vec3 meshData;
        meshData=glm::vec3(vertices[faceIndex[i]].x,vertices[faceIndex[i]].y,vertices[faceIndex[i]].z);
        meshVertices.push_back(meshData);

    }
}
std::vector<glm::vec3> Mesh::returnMesh()
{
    return meshVertices;
}
