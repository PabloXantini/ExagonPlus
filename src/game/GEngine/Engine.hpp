#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Shaders.hpp"
#include "../../resource.h"
#include "../Color.h"

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
        void updateBufferColorWeight(unsigned int VAO, std::vector<RGBColor>& colors);
        void clearBuffers();
        //Graph Methods
        void fixScreenProportion(GLFWwindow* window);
        void renderPolygon(unsigned int rVAO, unsigned int sides);
        void renderPolygon2(unsigned int rVAO, unsigned int vertexcount);
        void rotate3D(float time, float RX, float RY, float RZ);
        void changeHue(float change, float hueFactor, float hueSpeed);
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
    //Desvincular
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Faltaria que se guarden esos datos en un variable de objetos
    buffers.push_back(newBuffer);

    return newBuffer;
}

//Actualiza el peso de colores
void Engine::updateBufferColorWeight(unsigned int VBO, std::vector<RGBColor>& colors){
    int stride=6;
    std::vector<float> colorspace;
    for (auto& c : colors){
        pushColor(colorspace, c);
    }
    //Abre el buffer en cuestion
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    for (size_t i=0; i<colors.size();++i) {
        GLintptr offset = 3*sizeof(float) + i*stride*sizeof(float);
        glBufferSubData(GL_ARRAY_BUFFER, offset, 3*sizeof(float), &colorspace[i*3]);
    }
    //Desvincula en buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Limpia todos los buffers
void Engine::clearBuffers() {
    auto vaos = getAllVAOs(buffers);
    auto vbos = getAllVBOs(buffers);
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
}

//Render Methods
//Renderiza un poligono con indices
void Engine::renderPolygon(unsigned int rVAO, unsigned int nindexes) {
    BASIC.use();
    glBindVertexArray(rVAO);
    glDrawElements(GL_TRIANGLES, nindexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
//Renderiza un poligono con vertices
void Engine::renderPolygon2(unsigned int rVAO, unsigned int vertexcount){
    BASIC.use();
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexcount);
    glBindVertexArray(0);
}
//Arregla la resolucion de pantalla
void Engine::fixScreenProportion(GLFWwindow* window){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;
    int aspectLoc = glGetUniformLocation(BASIC.getID(), "uAspect");
    glUniform1f(aspectLoc, aspect);
}
//Transformaciones
void Engine::rotate3D(float time, float RX, float RY, float RZ){
    glm::mat4 rot = glm::mat4(1.0);
    rot = glm::rotate(rot, glm::radians(time*RX), glm::vec3(1.0,0.0,0.0)); //Rotation en el eje X
    rot = glm::rotate(rot, glm::radians(time*RY), glm::vec3(0.0,1.0,0.0)); //Rotation en el eje Y
    rot = glm::rotate(rot, glm::radians(time*RZ), glm::vec3(0.0,0.0,1.0)); //Rotation en el eje Z
    BASIC.setMat4("transRotation",rot);
}
//Cambia el HUE del escenario
void Engine::changeHue(float time, float hueFactor, float hueSpeed){
    BASIC.setFloat("uTime",time);
    BASIC.setFloat("HueFactor",hueFactor);
    BASIC.setFloat("HueSpeed",hueSpeed);
}

void Engine::clearShaders(){
    BASIC.kill();
}

#endif