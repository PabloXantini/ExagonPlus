#ifndef TRANSFORM_USER_GL_HPP
#define TRANSFORM_USER_GL_HPP

#include "../include/GCore.hpp"
#include "Transform3D.hpp"

class TransformUserGL : public TransformUser {
    public:
        TransformUserGL(){}
        ~TransformUserGL(){}
        Transform3D* useTransform3D() override {
            return new Transform3D_GL();
        }
};

#endif