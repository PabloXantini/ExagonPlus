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
ExagonPanel::ExagonPanel(const ExagonGameProcess& gameProcess) : gameProcess(gameProcess) {
    setupBuffers();
}

//Getters
unsigned int ExagonPanel::getVAO() const {
    return VAO;
}

//Configura los buffers
void ExagonPanel::setupBuffers() {
    const std::vector<float>& vertices = gameProcess.getBG().getVertexs();
    unsigned int vnum = gameProcess.getBG().getVertexCount();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vnum * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ExagonPanel::paint(){
    background.show(getVAO());
}

#endif