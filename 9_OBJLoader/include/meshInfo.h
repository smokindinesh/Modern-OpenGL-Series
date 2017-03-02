#pragma once
#include <glm\glm.hpp>
struct MeshVert {
	glm::vec3 vertCord;
	MeshVert(){}
	MeshVert(glm::vec3 pos)
	{
		vertCord = pos;
	}
};
struct vertIndex{
    int faceIndex;
    vertIndex();
    vertIndex(int x){
        faceIndex = x;
    };
};
struct MeshVertTex {
	glm::vec3 vertCord;
	glm::vec2 texCord;
	MeshVertTex() {}
	MeshVertTex(glm::vec3 pos, glm::vec2 tex)
	{
		vertCord = pos;
		texCord = tex;
	}
};
struct vertTexIndex{
    int faceIndex;
    int texIndex;
    vertTexIndex();
    vertTexIndex(int x,int y){
        faceIndex = x;
        texIndex = y;
    };
};
struct MeshVertTexNorm {
	glm::vec3 vertCord;
	glm::vec2 texCord;
	glm::vec3 normCord;
	MeshVertTexNorm () {}
	MeshVertTexNorm(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm)
	{
		vertCord = pos;
		texCord = tex;
		normCord = norm;
	}
};
struct vertTexNormIndex{
    int faceIndex;
    int texIndex;
    int normIndex;
    vertTexNormIndex();
    vertTexNormIndex(int x,int y,int z){
        faceIndex=x;
        texIndex=y;
        normIndex=z;
    };
};
