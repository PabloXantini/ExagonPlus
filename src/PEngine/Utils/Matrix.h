#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>

struct Mat2f {
    float mat2x2[2][2];
    Mat2f(float diagonal_value){
        make_diagonal(diagonal_value);
    }
    void make_diagonal(float diagonal_value){
        memset(mat2x2, 0, sizeof(mat2x2));
        for(int i=0; i<2; i++){
            mat2x2[i][i]= diagonal_value;
        }
    }
};

struct Mat3f {
    float mat3x3[3][3];
    Mat3f(float diagonal_value){
        make_diagonal(diagonal_value);
    }
    void make_diagonal(float diagonal_value){
        memset(mat3x3, 0, sizeof(mat3x3));
        for(int i=0; i<3; i++){
            mat3x3[i][i]= diagonal_value;
        }
    }
};

struct Mat4f {
    float mat4x4[4][4];
    Mat4f(float diagonal_value){
        make_diagonal(diagonal_value);
    }
    void make_diagonal(float diagonal_value){
        memset(mat4x4, 0, sizeof(mat4x4));
        for(int i=0; i<4; i++){
            mat4x4[i][i]= diagonal_value;
        }
    }
};

#endif