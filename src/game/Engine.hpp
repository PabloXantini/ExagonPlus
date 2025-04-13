#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
    private:
        void setupShaders();
    public:
        unsigned int shaderProgram;
        Engine();
        void renderPolygon(unsigned int rVAO, unsigned int shaderProgram, unsigned int sides);
};

Engine::Engine() {
    setupShaders();
}

void Engine::setupShaders() {
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "   vec3 scaled = aPos;\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(0.39f, 0.44f, 0.91f, 1.0f);\n"
        "}\n\0";

    //Parte para crear y compilar un VertexShader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Parte para crear y compilar un fragmentShader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Parte del programa
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Engine::renderPolygon(unsigned int rVAO, unsigned int shaderProgram, unsigned int sides){
    glUseProgram(shaderProgram);
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sides/3);
    glBindVertexArray(0);
}

#endif