#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <fstream>
#include <sstream>

class Engine {
    private:
        void setupShaders();
        unsigned int loadShader(const char* vertexPath, const char* fragmentPath);
    public:
        unsigned int shaderProgram;
        Engine();
        void fixScreenProportion(GLFWwindow* window);
        void renderPolygon(unsigned int rVAO, unsigned int shaderProgram, unsigned int sides);
};

Engine::Engine() {
    setupShaders();
}

void Engine::setupShaders() {
    shaderProgram=loadShader("shaders/shape.vert","shaders/shape.frag");
    //std::cout<<"Hola?"<<std::endl;
    std::cout<<shaderProgram<<std::endl;
    /*
    //Aqui en su lugar cargare shaders uno por uno
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform float uAspect;\n"
        "void main() {\n"
        "   vec3 scaled = aPos;\n"
        "   scaled.x /= uAspect;\n"
        "   gl_Position = vec4(scaled, 1.0);\n"
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
    */
}

 unsigned int Engine::loadShader(const char* vertexPath, const char* fragmentPath){
    //Flujo de archivos
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    //Variables finales
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;  //Shaders
    int success;                    //Exito
    char infoLog[512];              //Info

    // Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader Program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void Engine::renderPolygon(unsigned int rVAO, unsigned int shaderProgram, unsigned int sides){
    glUseProgram(shaderProgram);
    glBindVertexArray(rVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sides);
    glBindVertexArray(0);
}

void Engine::fixScreenProportion(GLFWwindow* window){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;
    int aspectLoc = glGetUniformLocation(shaderProgram, "uAspect");
    glUniform1f(aspectLoc, aspect);
}

#endif