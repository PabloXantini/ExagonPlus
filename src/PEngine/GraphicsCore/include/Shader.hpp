#ifndef SHADER_INTERFACE_HPP
#define SHADER_INTERFACE_HPP

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
        /*
        virtual void compile(const char* vsSource, const char* fsSource, const char* gsSource){};
        */
        //Usar el shader
        virtual void use() = 0;
        //Setear atributos del shader en cuestion
        virtual void setBool(const std::string &name, bool value) const = 0;  
        virtual void setInt(const std::string &name, int value) const = 0;   
        virtual void setFloat(const std::string &name, float value) const = 0;
        virtual void setVec2(const std::string &name, float x, float y) const = 0;
        virtual void setVec3(const std::string &name, float x, float y, float z) const = 0;
        virtual void setVec4(const std::string &name, float x, float y, float z, float w) const = 0;
        //Quitar el shader
        virtual void kill() = 0;

};

#endif