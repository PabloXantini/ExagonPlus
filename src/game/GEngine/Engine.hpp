#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Shader.hpp"
#include "Shaders.hpp"
#include "../../resource.h"

#include <iostream>
//#include <fstream>
//#include <sstream>
#include <map>

class Engine {
    private:
        //Variables propias del motor
        std::map<ShaderName, unsigned int> shaders;
        void setupShaders();
        unsigned int loadShader(const char* vertexPath, const char* fragmentPath);
        Shader BASIC;
    public:
        Engine();
        //Getters
        unsigned int getShaderProgram(ShaderName label){
            return shaders[label];
        }
        void fixScreenProportion(GLFWwindow* window);
        void renderPolygon(unsigned int rVAO, unsigned int sides);
        void clearShaders();
};

Engine::Engine()
    :BASIC(IDR_VSHADER1,IDR_FSHADER1)
{
    //setupShaders();
}

//Posibilly to deprecate
void Engine::setupShaders(){
    //Aqui se supone que cargo dinamicamente los shaders
    //shaders[BASIC]=loadShader("shaders/shape.vert","shaders/shape.frag"); 
}

void Engine::renderPolygon(unsigned int rVAO, unsigned int nindexes){
    BASIC.use();
    glBindVertexArray(rVAO);
    glDrawElements(GL_TRIANGLES, nindexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Engine::fixScreenProportion(GLFWwindow* window){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;
    int aspectLoc = glGetUniformLocation(BASIC.getID(), "uAspect");
    glUniform1f(aspectLoc, aspect);
}

void Engine::clearShaders(){
    for(const auto& [type, program] : shaders){
        glDeleteProgram(program);
        std::cout<<program<<std::endl;
    }
}

#endif