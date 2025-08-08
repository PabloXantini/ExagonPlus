#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 projection;

out vec4 oFragColor;
//uniform float uAspect;
void main() {
    oFragColor = aColor;
    vec3 scaled = aPos;
    //scaled.x /= uAspect;
    gl_Position = vec4(aPos, 1.0);
};