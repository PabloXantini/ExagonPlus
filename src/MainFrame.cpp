#include <windows.h>
#include <psapi.h>

#include "game/GEngine/Engine.hpp"
#include "game/ExagonPanel.hpp"

#include <iostream>
#include <vector>

//Declaracion de funciones
void printMemoryUsage();

//Variables para configurar al inicio de la aplicacion
//Titulo de la aplicación
const char TITLE[] = "ExagonPlus";
//Configuracion de la pantalla
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;
//Iconos de la aplicacion
std::vector<int> iconsref ={IDR_PNG1, IDR_PNG1};

//Arranca el juego
int main() {
    Engine engine; //Arranca el motor

    if(!engine.initWindow(SCR_WIDTH, SCR_HEIGHT, TITLE)) return -1;
    engine.setWindowsIcons(iconsref);
    engine.initWindowResizing();
    if(!engine.linkGLAD()) return -1;
    //engine.initShaders();
    engine.blockFPS(60);

    //Llamo a los objetos necesarios
    ExagonPanel panel(&engine);

    //Corredor del juego -- Lo puedo incluir en Engine
    while (engine.isWindowOpen()) {
        //events
        engine.pollInput();
        engine.rendWindowBackground();
        //render
        panel.show();
        //Debugging
        //printMemoryUsage();
        //handler
        engine.handle();
    }
    //Limpio todo al cerrar
    engine.close();
    engine.destroyWindow();

    return 0;
}

//==========================================DEBUGGING=========================================================
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        std::cout << "Memoria en uso: " << memCounter.WorkingSetSize / 1024 << " KB" << std::endl;
    }
}