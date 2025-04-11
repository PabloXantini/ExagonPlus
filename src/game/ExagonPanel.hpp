#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "../include/glad/glad.h"

#include "ExagonGameProcess.hpp"

class ExagonPanel {
public:
    ExagonPanel(const ExagonGameProcess &gameProcess);
    void setupBuffers();
    unsigned int getVAO() const;
private:
    unsigned int VAO, VBO;
    const ExagonGameProcess &gameProcess;
};

ExagonPanel::ExagonPanel(const ExagonGameProcess& gameProcess) : gameProcess(gameProcess) {
    setupBuffers();
}

//Configura los buffers
void ExagonPanel::setupBuffers() {
    const std::vector<float>& vertices = gameProcess.getBG().getVertex();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//Getters
unsigned int ExagonPanel::getVAO() const {
    return VAO;
}

#endif