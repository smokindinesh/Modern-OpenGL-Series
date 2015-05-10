#version 150

uniform sampler2D tex;
in vec2 textureCoord;
out vec4 finalColor;

void main() {
    //set every drawn pixel to white
    //finalColor = vec4(1.0, 1.0, 1.0, 1.0);
    finalColor = texture(tex,textureCoord);
}
