#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//Aspecto
uniform float uAspect;
//Transformaciones
uniform mat4 transRotation;

//colores a pasar
out vec3 oFragColor;

void main() {
    //Color
    oFragColor = aColor;
    //Posicion
    vec4 rotated = transRotation * vec4(aPos, 1.0);
    //Ajustar el aspecto
    rotated.x /= uAspect;
    //Setear la posicion final
    gl_Position = rotated;
};