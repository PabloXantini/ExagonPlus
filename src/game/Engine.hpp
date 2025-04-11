#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "ExagonPanel.hpp"

class Engine {
public:
    unsigned int shaderProgram;
    Engine();
    void render(const ExagonPanel& panel, unsigned int shaderProgram);
private:
    void setupShaders();
};

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

#endif