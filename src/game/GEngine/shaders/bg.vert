#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 toPos;

//Tipo de objeto
uniform int ObjectType;

//Escenario
//Vista y Camara
uniform mat4 Projection;
uniform mat4 View;
//Global
uniform mat4 Rotation;
//Transformaciones del Modelo
uniform mat4 Model;
//Polar Morphing
uniform float morphprogress;

//Pared
//Colapse
uniform float marginL;
uniform float marginR;
uniform float collapseprogress;

vec3 WallCollapseToCenter(vec3 from, float t) {
    from*=7;
    vec3 normal = normalize(from);
    from = mix(from, vec3(0.0,0.0,0.0), t);
    if(gl_VertexID==2){
        return from + normal * marginR;
    }else if(gl_VertexID==3){
        return from + normal * marginL;
    }else{
        return from;
    }
}

vec3 polarMorph(vec3 from, vec3 to, float t) {
    vec2 pA = from.xy;
    vec2 pB = to.xy;

    float rA = length(from.xy);
    float rB = length(to.xy);

    //Evaluar si alguno de los radios es muy pequenio
    if (rA < 0.001 && rB < 0.001)
        return vec3(0.0, 0.0, mix(from.z, to.z, t)); // ambos centros

    if (rA < 0.001)
        return mix(from, to, t); // o directamente return to;

    if (rB < 0.001)
        return mix(from, to, t); // o directamente return from;

    float aA = atan(pA.y, pA.x);
    float aB = atan(pB.y, pB.x);

    // Corrección para que el ángulo interpolado tome el camino más corto
    
    float delta = aB - aA;
    if (abs(delta) > 3.14159) {
        if (delta > 0.0)
            aA += 6.28318; // +2π
        else
            aB += 6.28318; // +2π
    }
    
    float radius = mix(rA, rB, t);
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
    vec3 collapsed = WallCollapseToCenter(mphPos, collapseprogress);
    vec3 FinalPos = mphPos;
    if(ObjectType==1){
        FinalPos = collapsed;
    }
    //Posicion
    vec4 result = Projection * View * Rotation * Model * vec4(FinalPos, 1.0); 
    gl_Position = vec4(result);
};