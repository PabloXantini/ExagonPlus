#pragma once
#ifndef SHADER_DATA_ADAPTER_H
#define SHADER_DATA_ADAPTER_H

#include "../../Utils/Matrix.h"
#include "Shader.hpp"

#include <cstring>

inline Mat4f fromGLMMat4(glm::mat4 glm_mat){
    Mat4f mat(1.0f);
    memcpy(mat.mat4x4, &glm_mat[0][0], sizeof(mat.mat4x4));
    return mat;
}

#endif