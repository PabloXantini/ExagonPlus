#version 330 core

in vec4 oFragColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(oFragColor);
}