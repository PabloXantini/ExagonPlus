#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//Aspecto
//uniform float uAspect;
//Vista
uniform mat4 transProjection;
//Camara
uniform mat4 transView;
//Transformaciones
uniform mat4 transRotation;
uniform mat4 transScale;

//colores a pasar
out vec3 oFragColor;

void main() {
    //Color
    oFragColor = aColor;
    //Posicion
    vec4 result = transProjection * transView * transRotation * transScale * vec4(aPos, 1.0); 
    gl_Position = vec4(result);
};