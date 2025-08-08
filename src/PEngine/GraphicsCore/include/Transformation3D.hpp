#ifndef TRANSFORMATION_3D_INTERFACE_HPP
#define TRANSFORMATION_3D_INTERFACE_HPP

#include "Shader.hpp"

class Transform3D {
    public:
        Transform3D(){}
        virtual ~Transform3D(){}
        virtual void rotate(float DegX = 0.0f, float DegY = 0.0f, float DegZ = 0.0f) = 0;
        virtual void translate(Vec3f objective) = 0;
        virtual void scale(float factor) = 0;
        virtual void scale_local(Vec3f factor) = 0;
        virtual void reset() = 0;
        virtual void apply(IShader* shader, const std::string &name) = 0;
};

#endif