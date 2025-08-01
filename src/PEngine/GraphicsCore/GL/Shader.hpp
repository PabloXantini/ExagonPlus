#ifndef SHADER_OPENGL_INTERFACE_HPP
#define SHADER_OPENGL_INTERFACE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Shader.hpp"

class ShaderGL : public IShader {
    public:
        ShaderGL() = default;
        virtual ~ShaderGL() = default;
        virtual void setVec2(const std::string &name, const glm::vec2 &value) const = 0;
        virtual void setVec3(const std::string &name, const glm::vec3 &value) const = 0;
        virtual void setVec4(const std::string &name, const glm::vec4 &value) const = 0;
        virtual void setMat2(const std::string &name, const glm::mat2 &mat) const = 0;
        virtual void setMat3(const std::string &name, const glm::mat3 &mat) const = 0;
        virtual void setMat4(const std::string &name, const glm::mat4 &mat) const = 0;
};

#endif