#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include <iostream>

//Configuracion de pantalla
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

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
    //Inicializa todo
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crea la ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ExagonPlus", NULL, NULL);
    if(window==NULL){
        std::cout <<"La creación de la ventana ha fallado" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Tamanio de la ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Corro el inicializador de OpenGL *(glad)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "La inicializacion de GLAD ha fallado" << std::endl;
    return -1;
    }
    
    //Motor
    while(!glfwWindowShouldClose(window)){
        //Inputs
        processInput(window);
        //Render
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
    return 0;
}