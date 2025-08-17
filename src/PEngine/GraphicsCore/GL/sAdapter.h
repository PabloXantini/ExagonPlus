#pragma once
#ifndef SHADER_DATA_ADAPTER_H
#define SHADER_DATA_ADAPTER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utils/Position.h"
#include "../../Utils/Matrix.h"

#include <cstring>

//Standard cast
inline Vec2f fromGLMVec2(glm::vec2 glm_vec2){
    return {glm_vec2.x, glm_vec2.y};
}
inline Vec3f fromGLMVec3(glm::vec3 glm_vec3){
    return {glm_vec3.x, glm_vec3.y, glm_vec3.z};
}
inline Mat4f fromGLMMat4(glm::mat4 glm_mat){
    Mat4f mat(1.0f);
    memcpy(mat.mat4x4, &glm_mat[0][0], sizeof(mat.mat4x4));
    return mat;
}
//Non standard cast
inline glm::vec2 fromVec2f(Vec2f vec2){
    return glm::vec2(vec2.X, vec2.Y);
}
inline glm::vec3 fromVec3f(Vec3f vec3){
    return glm::vec3(vec3.X, vec3.Y, vec3.Z);
}
//Standard operator overload with cast
inline Vec3f operator+(const glm::vec3& vec3, const Vec3f& stdvec3){
    return {stdvec3.X + vec3.x, stdvec3.Y + vec3.y, stdvec3.Z + vec3.z};
}
inline Vec3f operator+(const Vec3f& stdvec3, const glm::vec3& vec3){
    return {stdvec3.X + vec3.x, stdvec3.Y + vec3.y, stdvec3.Z + vec3.z};;
}
inline Vec3f& operator+=(Vec3f& stdvec3, const glm::vec3& vec3){
    stdvec3.X+=vec3.x;
    stdvec3.Y+=vec3.y;
    stdvec3.Z+=vec3.z;
    return stdvec3;
}

#endif