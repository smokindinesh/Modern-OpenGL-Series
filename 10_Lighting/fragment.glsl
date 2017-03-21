#version 150

uniform sampler2D tex;
in vec2 textureCoord;
out vec4 finalColor;

void main() {
    //set every drawn pixel to bmp image pixel
    finalColor = texture(tex,textureCoord);
}
