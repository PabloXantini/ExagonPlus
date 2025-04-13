#version 330 core

layout (location = 0) in vec3 aPos;
    uniform float uAspect;
void main() {
    vec3 scaled = aPos;
    scaled.x /= uAspect;
    gl_Position = vec4(scaled, 1.0);
};