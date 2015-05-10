#version 420

uniform mat4 model;
uniform mat4 prespective;
uniform mat4 camera;
in vec3 vPosition;
in vec4 vColor;
out vec4 outColor;
void main() {
    // does not alter the verticies at all
    gl_Position = prespective*camera*model*vec4(vPosition, 1);
    outColor=vColor;
}
