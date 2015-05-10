#version 150

uniform mat4 model;
uniform mat4 prespective;
uniform mat4 camera;
in vec3 vPosition;
in vec2 vertTextCoord;
out vec2 textureCoord;
void main() {
    // does not alter the verticies at all
    gl_Position = prespective*camera*model*vec4(vPosition, 1);
    textureCoord=vertTextCoord;
}
