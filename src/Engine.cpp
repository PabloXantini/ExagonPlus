#include "../include/glad/glad.h"

#include "game/Engine.hpp"
#include <iostream>
#include <vector>

Engine::Engine() {
    setupShaders();
}

void Engine::setupShaders() {
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Engine::render(const ExagonPanel& panel, unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(panel.getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
/*
class Engine {
    //Pruebas
    public:
    const char* vertexShaderSource;
    const char* fgvertexShaderSource;
    
    std::vector<float> vertexs;
    unsigned int VBO, VAO;
    
    Engine();
        unsigned int initEngine();
        void buildvertexShader(unsigned int &vshader, const char* src);
        void buildfgvertexShader(unsigned int &fgvshader, const char* src);
        void linkShader(unsigned int &shprogram, unsigned int &vshader, unsigned int &fgvshader);
        void clearBuffers(int shaders);
    };
    
    Engine::Engine() {
        vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
        fgvertexShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
        vertexs = {
            -0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f 
        };
    };
    
void Engine::buildvertexShader(unsigned int &vshader, const char* src){
    //Hace build del motor de formas
    //vshader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &src, NULL);
    glCompileShader(vshader);
    //Depurador
    int success;
    char infoLog[512];
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vshader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Engine::buildfgvertexShader(unsigned int &fgvshader, const char* src){
    //Hace build del motor de color de formas
    //fgvshader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fgvshader, 1, &src, NULL);
    glCompileShader(fgvshader);
    //Depurador
    int success;
    char infoLog[512];
    glGetShaderiv(fgvshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fgvshader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Engine::linkShader(unsigned int &shprogram, unsigned int &vshader, unsigned int &fgvshader){
    glAttachShader(shprogram, vshader);
    glAttachShader(shprogram, fgvshader);
    glLinkProgram(shprogram);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shprogram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shprogram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vshader);
    glDeleteShader(fgvshader);
}

unsigned int Engine::initEngine(){
    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    unsigned int fgvertexShader=glCreateShader(GL_FRAGMENT_SHADER);;
    unsigned int shvprogram=glCreateProgram();
    //Compila los shader
    //Shader de formas
    buildvertexShader(vertexShader, vertexShaderSource);
    buildfgvertexShader(fgvertexShader, fgvertexShaderSource);
    linkShader(shvprogram,vertexShader,fgvertexShader);
    
    //Motor de formas
    //Genera buffers
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    
    //Copia para que los use openGL
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs.data()), vertexs.data(), GL_DYNAMIC_DRAW);
    
    //Setup
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    return shvprogram;
}

void Engine::clearBuffers(int shaders) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaders);
}

#endif
*/

