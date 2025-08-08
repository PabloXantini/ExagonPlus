#pragma once
#ifndef SHADER_GL33_HPP
#define SHADER_GL33_HPP

#include "../Shader.hpp"

class ShaderGL33 : public ShaderGL {
    private:
        unsigned int ShaderProgramID;
        void checkCompileErrors(unsigned int shader, std::string type);
    public:
        ShaderGL33() = default;
        ~ShaderGL33() = default;
        void load(const std::vector<ShaderPartData>& parts) override;
        void use() override;
        //Primitives
        void setBool(const std::string &name, bool value) const override;  
        void setInt(const std::string &name, int value) const override;   
        void setFloat(const std::string &name, float value) const override;
        //Vector2
        void setVec2(const std::string &name, const glm::vec2 &value) const override;
        void setVec2(const std::string &name, const Vec2f& vec2) const override;
        void setVec2(const std::string &name, float x, float y) const override;
        //Vector3
        void setVec3(const std::string &name, const glm::vec3 &value) const override;
        void setVec3(const std::string &name, const Vec3f& vec3) const override;
        void setVec3(const std::string &name, float x, float y, float z) const override;
        //Vector4
        void setVec4(const std::string &name, const glm::vec4 &value) const override;
        void setVec4(const std::string &name, float x, float y, float z, float w) const override;
        //Matrix2x2
        void setMat2(const std::string &name, const glm::mat2 &mat) const override;
        void setMat2(const std::string &name, const Mat2f& mat) const override;
        //Matrix3x3
        void setMat3(const std::string &name, const glm::mat3 &mat) const override;
        void setMat3(const std::string &name, const Mat3f& mat) const override;
        //Matrix4x4
        void setMat4(const std::string &name, const glm::mat4 &mat) const override;
        void setMat4(const std::string &name, const Mat4f& mat) const override;
        void kill() override;
};

#endif