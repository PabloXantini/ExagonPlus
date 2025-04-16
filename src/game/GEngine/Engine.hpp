#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../include/glad/glad.h"

#include "Shader.hpp"
#include "Shaders.hpp"
#include "../../resource.h"

#include <iostream>
#include <vector>
#include <map>

struct ObjectBuffer {
    unsigned int VAO; //Vertex Array Object: Define el objecto de vertices
    unsigned int VBO; //Vertex Buffer Object: Define en donde se van a guardar los vertices
    unsigned int EBO=0; //Element Buffer Object: Define como se van a dibujar los vertices
};

class Engine {
    private:
        //Variables propias del motor
        std::vector<ObjectBuffer> buffers={};
        std::map<ShaderName, unsigned int> shaders; //Posibility to deprecate
        void setupShaders();
        Shader BASIC;
    public:
        //Constructor
        Engine();
        //Getters
        unsigned int getShaderProgram(ShaderName label){
            return shaders[label];
        }
        std::vector<unsigned int> getAllVAOs(const std::vector<ObjectBuffer>& buffers) {
            std::vector<unsigned int> VAOs;
            VAOs.reserve(buffers.size());
            for (const auto& buffer : buffers) {
                VAOs.push_back(buffer.VAO);
            }
            return VAOs;
        }
        
        std::vector<unsigned int> getAllVBOs(const std::vector<ObjectBuffer>& buffers) {
            std::vector<unsigned int> VBOs;
            VBOs.reserve(buffers.size());
            for (const auto& buffer : buffers) {
                VBOs.push_back(buffer.VBO);
            }
            return VBOs;
        }
        //Memory Methods
        ObjectBuffer createBuffer3D(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, bool hasColor);
        void clearBuffers();
        //Graph Methods
        void fixScreenProportion(GLFWwindow* window);
        void renderPolygon(unsigned int rVAO, unsigned int sides);
        void renderPolygon2(unsigned int rVAO, unsigned int vertexcount);
        void clearShaders();
};

Engine::Engine()
    :BASIC(IDR_VSHADER2,IDR_FSHADER2)
{
    std::cout<<"Oh me creooo, dice Engine o Motor"<<std::endl;
}

//Posibilly to deprecate
void Engine::setupShaders(){
    //Aqui se supone que cargo dinamicamente los shaders
    //Si se me complica manejar los shader aca, lo borro
}

//Memory Methods
//Crea un buffer para un objeto
ObjectBuffer Engine::createBuffer3D(const std::vector<float>& verts, const std::vector<unsigned int>* indexes, bool hasColor){
    struct ObjectBuffer newBuffer;

    //Asigno IDs para VAO, VBO, EBO
    glGenVertexArrays(1, &newBuffer.VAO);
    glGenBuffers(1, &newBuffer.VBO);
    //Opcional
    if(indexes) glGenBuffers(1, &newBuffer.EBO);

    //Asignacion de memoria para VAO
    glBindVertexArray(newBuffer.VAO);
    //Asignacion de memoria para VBO
    glBindBuffer(GL_ARRAY_BUFFER, newBuffer.VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);
    //Opcional: Asignacion de memoria para EBO
    if(indexes){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newBuffer.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes->size() * sizeof(unsigned int), indexes->data(), GL_STATIC_DRAW);
    }
    //Setup de argumentos para el buffer
    if(hasColor){
        //Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
    }else{
        //Color
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Faltaria que se guarden esos datos en un variable de objetos
    buffers.push_back(newBuffer);

    return newBuffer;
}

//Limpia todos los buffers
void Engine::clearBuffers() {
    auto vaos = getAllVAOs(buffers);
    auto vbos = getAllVBOs(buffers);
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
}

//Render Methods
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