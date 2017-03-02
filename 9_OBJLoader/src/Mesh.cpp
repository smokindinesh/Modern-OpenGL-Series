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
            double x,y,z;
            v>>x;v>>y;v>>z;
            vertices.push_back(glm::vec3(x,y,z));
      }
      else if (line.substr(0,3)=="vt "){
            std::istringstream v(line.substr(3));
            double x,y;
            v>>x;v>>y;
            texture.push_back(glm::vec2(x,y));
      }
      else if (line.substr(0,3)=="vn "){
            std::istringstream v(line.substr(3));
            double x,y,z;
            v>>x;v>>y;v>>z;
            normal.push_back(glm::vec3(x,y,z));
      }
      else if(line.substr(0,2)=="f "){
        std::istringstream v(line.substr(2));
        GLuint a,b,c;
        if(normal.size()!=0){
            std::string aa[3];
            v>>aa[0];v>>aa[1];v>>aa[2];
                for(int i=0;i<3;i++){
                    std::istringstream v(aa[i]);
                    v>>a;
                    if (v.peek() == '/')
                    v.ignore();
                    v>>b;
                    if (v.peek() == '/')
                    v.ignore();
                    v>>c;
                    a--;b--;c--;
                    vertTexNormInd.push_back(vertTexNormIndex(a,b,c));
                }
        }else if(normal.size()==0 && texture.size()!=0){
            std::string aa[3];
            v>>aa[0];v>>aa[1];v>>aa[2];
                for(int i=0;i<3;i++){
                    std::istringstream v(aa[i]);
                    v>>a;
                    if (v.peek() == '/')
                    v.ignore();
                    v>>b;
                    a--;b--;
                    vertTexInd.push_back(vertTexIndex(a,b));
                }
        }else if(normal.size()==0 && texture.size()==0 && vertices.size()!=0){
            v>>a;v>>b;v>>c;
            a--;b--;c--;
            vertInd.push_back(vertIndex(a));
            vertInd.push_back(vertIndex(b));
            vertInd.push_back(vertIndex(c));
        }
      }
    }
    for(unsigned int i=0;i<vertTexNormInd.size();i++)
    {
        glm::vec3 meshData;
        glm::vec2 texData;
        glm::vec3 normData;

        meshData=glm::vec3(vertices[vertTexNormInd[i].faceIndex].x,vertices[vertTexNormInd[i].faceIndex].y,vertices[vertTexNormInd[i].faceIndex].z);
        texData=glm::vec2(texture[vertTexNormInd[i].texIndex].x,texture[vertTexNormInd[i].texIndex].y);
        normData=glm::vec3(vertices[vertTexNormInd[i].normIndex].x,vertices[vertTexNormInd[i].normIndex].y,vertices[vertTexNormInd[i].normIndex].z);

        meshVertTexNorm.push_back(MeshVertTexNorm(meshData,texData,normData));

    }
    for(unsigned int i=0;i<vertTexInd.size();i++)
    {
        glm::vec3 meshData;
        glm::vec2 texData;

        meshData=glm::vec3(vertices[vertTexInd[i].faceIndex].x,vertices[vertTexInd[i].faceIndex].y,vertices[vertTexInd[i].faceIndex].z);
        texData=glm::vec2(texture[vertTexInd[i].texIndex].x,texture[vertTexInd[i].texIndex].y);

        meshVertTex.push_back(MeshVertTex(meshData,texData));

    }
    for(unsigned int i=0;i<vertInd.size();i++)
    {
        glm::vec3 meshData;

        meshData=glm::vec3(vertices[vertInd[i].faceIndex].x,vertices[vertInd[i].faceIndex].y,vertices[vertInd[i].faceIndex].z);

        meshVert.push_back(MeshVert(meshData));

    }
}

std::vector<MeshVert> Mesh::returnMeshVert()
{
    return meshVert;
}
std::vector<MeshVertTex> Mesh::returnMeshVertTex()
{
    return meshVertTex;
}
std::vector<MeshVertTexNorm> Mesh::returnMeshVertTexNorm()
{
    return meshVertTexNorm;
}
