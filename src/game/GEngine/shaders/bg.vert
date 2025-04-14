#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in int colorIndex;

//aspecto
uniform float uAspect;
//rango de colores
uniform vec3 pcolors[50]

out vec3 FragColor;

void main() {
    //Color
    FragColor = pcolors[colorIndex];
    //Posicion
    vec3 scaled = aPos;
    scaled.x /= uAspect;
    gl_Position = vec4(scaled, 1.0);
};