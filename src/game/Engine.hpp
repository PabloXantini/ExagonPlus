#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Shaders.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class Engine {
    private:
        std::map<Shader, unsigned int> shaders;
        void setupShaders();
        unsigned int loadShader(const char* vertexPath, const char* fragmentPath);
    public:
        Engine();
        //Getters
        unsigned int getShaderProgram(Shader label){
            return shaders[label];
        }
        void fixScreenProportion(GLFWwindow* window, unsigned int shaderProgram);
        void renderPolygon(unsigned int rVAO, unsigned int shaderProgram, unsigned int sides);
        void clearShaders();
};

Engine::Engine() {
    setupShaders();
}

void Engine::setupShaders() {
    shaders[BASIC]=loadShader("shaders/shape.vert","shaders/shape.frag");
}

unsigned int Engine::loadShader(const char* vertexPath, const char* fragmentPath){
    //Flujo de archivos
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    //Variables finales
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;  //Shaders
    int success;                    //Exito
    char infoLog[512];              //Info

    // Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader Program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void Engine::renderPolygon(unsigned int rVAO, unsigned int shaderProgram, unsigned int sides){
    glUseProgram(shaderProgram);
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sides);
    glBindVertexArray(0);
}

void Engine::fixScreenProportion(GLFWwindow* window, unsigned int shaderProgram){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;
    int aspectLoc = glGetUniformLocation(shaderProgram, "uAspect");
    glUniform1f(aspectLoc, aspect);
}

void Engine::clearShaders(){
    for(const auto& [type, program] : shaders){
        glDeleteProgram(program);
        std::cout<<program<<std::endl;
    }
}

#endif