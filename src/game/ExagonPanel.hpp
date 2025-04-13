#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "ExagonGameProcess.hpp"

class ExagonPanel {
    private:
        unsigned int VAO, VBO;
        const ExagonGameProcess &gameProcess;
        BG background;
    public:
        //Constructor
        ExagonPanel(const ExagonGameProcess &gameProcess);
        //Methods
        unsigned int getVAO() const;
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
unsigned int ExagonPanel::getVAO() const {
    return VAO;
}

//Configura los buffers
void ExagonPanel::setupBuffers() {
    const std::vector<float>& verts = background.getVertexs();
    unsigned int vnum = background.getVertexCount();
    /*
    std::cout << "Número de vértices: " << background.getVertexCount() << std::endl;
    for (float v : background.getVertexs()) {
        std::cout << v << " ";
    }
    */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ExagonPanel::paint(){
    background.show(getVAO());
}

#endif