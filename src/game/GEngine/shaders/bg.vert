#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 toPos;

//Aspecto
//uniform float uAspect;
//Vista
uniform mat4 transProjection;
//Camara
uniform mat4 transView;
//Transformaciones del Modelo
uniform mat4 transRotation;
uniform mat4 transScale;
//Polar Morphing
uniform float radius;
uniform float morphprogress;

vec3 polarMorph(vec3 from, vec3 to, float t) {
    vec2 pA = from.xy;
    vec2 pB = to.xy;

    float rA = length(from.xy);
    float rB = length(to.xy);

    float aA = atan(pA.y, pA.x);
    float aB = atan(pB.y, pB.x);

    if (rA < 0.001 && rB < 0.001)
        return vec3(0.0, 0.0, mix(from.z, to.z, t)); // ambos centros

    if (rA < 0.001)
        return mix(from, to, t); // o directamente return to;

    if (rB < 0.001)
        return mix(from, to, t); // o directamente return from;

    // Corrección para que el ángulo interpolado tome el camino más corto
    float delta = aB - aA;
    if (abs(delta) > 3.14159) {
        if (delta > 0.0)
            aA += 6.28318; // +2π
        else
            aB += 6.28318; // +2π
    }

    float angle = mix(aA, aB, t);
    float z = mix(from.z, to.z, t);

    return vec3(cos(angle)*radius, sin(angle)*radius, z);
}

//colores a pasar
out vec3 oFragColor;

void main() {
    //Color
    oFragColor = aColor;
    //Morphing polar
    vec3 mphPos = polarMorph(aPos, toPos, morphprogress);
    //Posicion
    vec4 result = transProjection * transView * transRotation * transScale * vec4(mphPos, 1.0);
    //vec4 result = transProjection * transView * transRotation * transScale * vec4(aPos, 1.0); 
    gl_Position = vec4(result);
};