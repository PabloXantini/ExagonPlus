#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "ExagonGameProcess.hpp"

#include <vector>

struct ObjectBuffer {
    unsigned int VAO; //Vertex Array Object: Define el objecto de vertices
    unsigned int VBO; //Vertex Buffer Object: Define en donde se van a guardar los vertices
    unsigned int EBO=0; //Element Buffer Object: Define como se van a dibujar los vertices
};

class ExagonPanel {
    private:
        std::vector<ObjectBuffer> buffers={};
        const ExagonGameProcess &gameProcess;
        BG background;
    public:
        //Constructor
        ExagonPanel(const ExagonGameProcess &gameProcess);
        //Methods
        unsigned int getVAO(unsigned int index) const;
        std::vector<unsigned int> getAllVAOs(const std::vector<ObjectBuffer>& buffers);
        std::vector<unsigned int> getAllVBOs(const std::vector<ObjectBuffer>& buffers);
        ObjectBuffer createBuffer(const std::vector<float>& verts, const std::vector<unsigned int>* indexes);
        void setupBuffers();
        void clearBuffers();
        void paint();
};

//Constructor
ExagonPanel::ExagonPanel(const ExagonGameProcess& gameProcess)
    :gameProcess(gameProcess),
    background(0.9f,5) 
{
    setupBuffers();
}

//Getters
unsigned int ExagonPanel::getVAO(unsigned int index) const {
    return this->buffers.at(index).VAO;
}

std::vector<unsigned int> ExagonPanel::getAllVAOs(const std::vector<ObjectBuffer>& buffers) {
    std::vector<unsigned int> VAOs;
    VAOs.reserve(buffers.size());
    for (const auto& buffer : buffers) {
        VAOs.push_back(buffer.VAO);
    }
    return VAOs;
}

std::vector<unsigned int> ExagonPanel::getAllVBOs(const std::vector<ObjectBuffer>& buffers) {
    std::vector<unsigned int> VBOs;
    VBOs.reserve(buffers.size());
    for (const auto& buffer : buffers) {
        VBOs.push_back(buffer.VBO);
    }
    return VBOs;
}

//Crea un buffer para un objeto
ObjectBuffer ExagonPanel::createBuffer(const std::vector<float>& verts, const std::vector<unsigned int>* indexes){
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return newBuffer;
}

//Configura los buffers
void ExagonPanel::setupBuffers() {
    //Pusheo todas las cosas necesarias
    buffers.push_back(createBuffer(background.getVertexs(), &background.getIndexes()));
    /*
    std::cout << "[ ";
    for (float val : background.getIndexes()) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
    */
    //Se puede comentar esto para que solo me dibuje el orden de los poligonos
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ExagonPanel::clearBuffers() {
    auto vaos = getAllVAOs(buffers);
    auto vbos = getAllVBOs(buffers);
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
}

void ExagonPanel::paint(){
    background.show(this->getVAO(0));
}

#endif