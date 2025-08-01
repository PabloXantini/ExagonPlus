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
        //void compile(const char* vsSource, const char* fsSource, const char* gsSource) override;
        void use() override;
        void setBool(const std::string &name, bool value) const override;  
        void setInt(const std::string &name, int value) const override;   
        void setFloat(const std::string &name, float value) const override;
        void setVec2(const std::string &name, const glm::vec2 &value) const override;
        void setVec2(const std::string &name, float x, float y) const override;
        void setVec3(const std::string &name, const glm::vec3 &value) const override;
        void setVec3(const std::string &name, float x, float y, float z) const override;
        void setVec4(const std::string &name, const glm::vec4 &value) const override;
        void setVec4(const std::string &name, float x, float y, float z, float w) const override;
        void setMat2(const std::string &name, const glm::mat2 &mat) const override;
        void setMat3(const std::string &name, const glm::mat3 &mat) const override;
        void setMat4(const std::string &name, const glm::mat4 &mat) const override;
        void kill() override;
};

#endif