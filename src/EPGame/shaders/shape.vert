#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 Model;

out vec4 oFragColor;

void main() {
    oFragColor = aColor;
    vec4 result = Model * vec4(aPos, 1.0);
    gl_Position = vec4(result);
};