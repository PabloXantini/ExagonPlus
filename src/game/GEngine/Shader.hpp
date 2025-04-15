#ifndef SHADER_HPP
#define SHADER_HPP

#include <windows.h>

#include "../include/glad/glad.h"

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
        //Quitar el shader
        void kill();
};

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    //Espacios para alojar archivos(Nombre y Datos)
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //Garantizar que ifstream objects puede dar exepciones:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //Abre los archivos
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        //Lee a traves del buffer
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //Cierra archivos
        vShaderFile.close();
        fShaderFile.close();
        //Convierte a string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch(std::ifstream::failure&error){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << error.what() << std::endl;
    }
    //Variables finales
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;  //Shaders
    // Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Shader Program
    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertex);
    glAttachShader(ShaderProgramID, fragment);
    glLinkProgram(ShaderProgramID);
    checkCompileErrors(ShaderProgramID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(int vresID, int fresID) {
    std::string vertexCode = load(vresID);
    std::string fragmentCode = load(fresID);
    
    //std::cout << vertexCode << std::endl;
    //std::cout << fragmentCode << std::endl;
    
    //Variables finales
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;  //Shaders
    // Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Shader Program
    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertex);
    glAttachShader(ShaderProgramID, fragment);
    glLinkProgram(ShaderProgramID);
    checkCompileErrors(ShaderProgramID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ShaderProgramID);
}

void Shader::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(ShaderProgramID, name.c_str()), value); 
}

void Shader::kill(){
    glDeleteProgram(ShaderProgramID);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type){
    int success;
    char infoLog[1024];
    if (type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

std::string Shader::load(int resourceID) {
    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(resourceID), RT_RCDATA);
    if (!hResource) return "";
    HGLOBAL hLoadedResource = LoadResource(NULL, hResource);
    if (!hLoadedResource) return "";

    DWORD size = SizeofResource(NULL, hResource);
    const char* data = static_cast<const char*>(LockResource(hLoadedResource));

    return std::string(data, size);
}

#endif