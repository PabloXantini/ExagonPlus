#ifndef SHADER_INTERFACE_HPP
#define SHADER_INTERFACE_HPP

#include "../../Utils/Position.h"
#include "../../Utils/Matrix.h"

#include <iostream>
#include <vector>

enum class ShaderPart {
    VERTEX,
    FRAGMENT,
    GEOMETRY
};

struct ShaderPartData {
    ShaderPart part;
    //OPENGL DATA
    std::string glslCode;
    //OTRAS PLATAFORMAS QUE NI SE
};

class IShader {
    public:
        IShader() = default;
        virtual ~IShader() = default;
        virtual void load(const std::vector<ShaderPartData>& parts){};
        //Usar el shader
        virtual void use() = 0;
        //Setear atributos del shader en cuestion
        virtual void setBool(const std::string &name, bool value) const = 0;  
        virtual void setInt(const std::string &name, int value) const = 0;   
        virtual void setFloat(const std::string &name, float value) const = 0;
        //Vec2
        virtual void setVec2(const std::string &name, float x, float y) const = 0;
        virtual void setVec2(const std::string &name, const Vec2f& vec2) const = 0;
        //Vec3
        virtual void setVec3(const std::string &name, float x, float y, float z) const = 0;
        virtual void setVec3(const std::string &name, const Vec3f& vec3) const = 0;
        //Vec4
        virtual void setVec4(const std::string &name, float x, float y, float z, float w) const = 0;
        //Matrix2x2
        virtual void setMat2(const std::string &name, const Mat2f& mat) const = 0;
        //Matrix3x3
        virtual void setMat3(const std::string &name, const Mat3f& mat) const = 0;
        //Matrix4x4
        virtual void setMat4(const std::string &name, const Mat4f& mat) const = 0;
        //Quitar el shader
        virtual void kill() = 0;
};

#endif