#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include <iostream>

#include "ExagonPanel.cpp"
#include "Engine.cpp"

//Configuracion de pantalla
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

//Declaro los shaders
unsigned int shaders;

//Ajusta la pantalla
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

//Manejador de eventos de teclado
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){
    //Inicializa todo el contexto de la ventana
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crea la ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ExagonPlus", NULL, NULL);
    //Validar si se creo
    if(window==NULL){
        std::cout <<"La creación de la ventana ha fallado" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Tamanio de la ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    //Validar si el inicializador de OpenGL se ejecuto (glad)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "La inicializacion de GLAD ha fallado" << std::endl;
        return -1;
    }
    
    shaders=LoadEngine();
    
    //Blockeo FPS por rendimiento -- despue se ve
    glfwSwapInterval(1);
    
    //Motor
    while(!glfwWindowShouldClose(window)){
        //Inputs
        processInput(window);
        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        PaintGame(shaders); 
        //Interrupciones
        glfwSwapBuffers(window);
        glfwPollEvents();   
    }

    Clear(shaders);

    glfwTerminate();
    return 0;
}