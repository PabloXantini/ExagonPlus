#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//aspecto
uniform float uAspect;
//colores a pasar
out vec3 oFragColor;

void main() {
    //Color
    oFragColor = aColor;
    //Posicion
    vec3 scaled = aPos;
    scaled.x /= uAspect;
    gl_Position = vec4(scaled, 1.0);
};