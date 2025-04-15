#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Shader.hpp"
#include "Shaders.hpp"
#include "../../resource.h"

#include <iostream>
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
        void renderPolygon2(unsigned int rVAO, unsigned int vertexcount);
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
    //Si se me complica manejar los shader aca, lo borro
}

void Engine::renderPolygon(unsigned int rVAO, unsigned int nindexes) {
    BASIC.use();
    glBindVertexArray(rVAO);
    glDrawElements(GL_TRIANGLES, nindexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Engine::renderPolygon2(unsigned int rVAO, unsigned int vertexcount){
    BASIC.use();
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexcount);
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
    BASIC.kill();
}

#endif