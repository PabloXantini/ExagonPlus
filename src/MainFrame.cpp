#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "game/ExagonGameProcess.hpp"
#include "game/ExagonPanel.hpp"
#include "game/Engine.hpp"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Configuracion de la pantalla
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

//Arranca el juego
int main() {
    //Inicializa el contexto de la pantalla
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Crea la ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hexagon Game", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //instancia la ventana
    glfwMakeContextCurrent(window);
    //Setea el tamanio de la ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Evalua si arranco GLAD(El linker para usar OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Llamo a los objetos necesarios
    ExagonGameProcess gameProcess;
    ExagonPanel panel(gameProcess);
    Engine engine;

    //Bloqueo de FPS
    glfwSwapInterval(1);

    //Corredor del juego -- Lo puedo incluir en Engine
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        engine.render(panel, engine.shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Cierra la ventana
    glfwTerminate();
    return 0;
}

//Eventos de teclado
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//Ajustar el tamanio de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}