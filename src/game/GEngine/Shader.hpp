#ifndef SHADER_HPP
#define SHADER_HPP

#include <windows.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    private:
        unsigned int ShaderProgramID;
        void checkCompileErrors(unsigned int shader, std::string type);
        std::string load(int resourceID);
    public:
        //Constructor
        Shader(int vresID, int fresID);
        Shader(const char* vertexPath, const char* fragmentPath);
        //Getters
        unsigned int getID(){
            return ShaderProgramID;
        }
        //Metodos
        //Usar el shader
        void use();
        //Para setear atributos en los GLSL a traves de uniform
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        //Quitar el shader
        void kill();
};

#endif