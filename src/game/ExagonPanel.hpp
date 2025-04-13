#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "ExagonGameProcess.hpp"

#include <vector>

struct ObjectBuffer {
    unsigned int VAO; 
    unsigned int VBO;
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
        ObjectBuffer createBuffer(const std::vector<float>& verts);
        void setupBuffers();
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
    return buffers.at(index).VAO;
}

//Crea un buffer para un objeto
ObjectBuffer ExagonPanel::createBuffer(const std::vector<float>& verts){
    struct ObjectBuffer newBuffer;
    glGenVertexArrays(1, &newBuffer.VAO);
    glGenBuffers(1, &newBuffer.VBO);
    
    glBindVertexArray(newBuffer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, newBuffer.VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return newBuffer;
}

//Configura los buffers
void ExagonPanel::setupBuffers() {
    //Pusheo todas las cosas necesarias
    buffers.push_back(createBuffer(background.getVertexs()));

}

void ExagonPanel::paint(){
    background.show(getVAO(0));
}

#endif