#version 150

in vec4 outColor;
out vec4 finalColor;

void main() {
    //set every drawn pixel to white
    //finalColor = vec4(1.0, 1.0, 1.0, 1.0);
    finalColor = outColor;
}
