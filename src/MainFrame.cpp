#include <windows.h>
#include <psapi.h>

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include "game/GEngine/Engine.hpp"
#include "game/ExagonPanel.hpp"
//#include "ImageProcessor.cpp"

#include <iostream>
#include <vector>

//Declaracion de funciones
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//GLFWimage load_icon(int resID);
void printMemoryUsage();

//Variables para configurar al inicio de la aplicacion
//Titulo de la aplicación
const char TITLE[] = "ExagonPlus";
//Configuracion de la pantalla
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;
//Iconos de la aplicacion
//GLFWimage icons[2];
std::vector<int> iconsref ={IDR_PNG1, IDR_PNG1};

//Arranca el juego
int main() {
    //icons[0] = load_icon(IDR_PNG1);
    //icons[1] = load_icon(IDR_PNG1);
    //Inicializa el contexto de la pantalla
    /*
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */
    //Crea la ventana
    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ExagonPlus", NULL, NULL);
    /*
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    */
    //instancia la ventana
    /*
    glfwMakeContextCurrent(window);
    //Setea el tamanio de la ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glfwSetWindowIcon(window, 2, icons);

    delete[] icons[0].pixels;  // Liberar memoria después de usarla
    delete[] icons[1].pixels;  // Liberar memoria después de usarla
    */
    //Evalua si arranco GLAD(El linker para usar OpenGL)
    /*
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    */
    Engine engine; //Arranca el motor

    if(!engine.initWindow(SCR_WIDTH, SCR_HEIGHT, TITLE)) return -1;
    engine.setWindowsIcons(iconsref);
    engine.initWindowResizing();
    if(!engine.linkGLAD()) return -1;
    engine.initShaders();
    engine.blockFPS(60);

    //Llamo a los objetos necesarios
    ExagonPanel panel(&engine);

    //Bloqueo de FPS
    //glfwSwapInterval(1);

    
    //Corredor del juego -- Lo puedo incluir en Engine
    while (engine.isWindowOpen()) {
        //events
        //processInput(window);
        engine.pollInput();
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        engine.rendWindowBackground();
        //render
        panel.run();
        //Debugging
        //printMemoryUsage();
        //handler
        engine.handle();
        //glfwSwapBuffers(window);
        //glfwPollEvents();
    }
    //Limpio todo al cerrar
    engine.close();
    engine.destroyWindow();
    //panel.clearEngine(); //Motor


    //Cierra la ventana
    //glfwTerminate();
    return 0;
}

/*
//Eventos de teclado
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
*/
/*
//Ajustar el tamanio de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout<<"Cambio"<<std::endl;
}

//Aniade el icono del programa
GLFWimage load_icon(int resID) {
    GLFWimage image;
    int width, height;
    image.pixels = loadImage(resID, width, height);
    image.width = width;
    image.height = height;
    return image;
}
*/
//==========================================DEBUGGING=========================================================
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        std::cout << "Memoria en uso: " << memCounter.WorkingSetSize / 1024 << " KB" << std::endl;
    }
}