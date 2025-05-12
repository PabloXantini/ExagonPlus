#include <windows.h>
#include <psapi.h>

#include "game/GEngine/Engine.hpp"
#include "game/AEngine/Engine.hpp"
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
    Engine engine;          //Arranca el motor grafico
    AudioEngine aengine;    //Arranca el motor de sonido

    //Inicializar el motor grafico
    if(!engine.initWindow(SCR_WIDTH, SCR_HEIGHT, TITLE)) return -1;
    engine.setWindowsIcons(iconsref);
    engine.initKeyboardListening();
    engine.initWindowResizing();
    if(!engine.linkGLAD()) return -1;
    engine.blockFPS(60);

    //Inicializar el motor de sonido
    if(!aengine.init()) return -1;

    //Llamo a los objetos necesarios
    ExagonPanel panel(&engine, &aengine);

    //Corredor del juego -- Lo puedo incluir en Engine
    while (engine.isWindowOpen()) {
        engine.rendWindowBackground();
        //render
        panel.show();
        //Debugging
        //printMemoryUsage();
        //handler
        engine.handle();
    }
    //Limpio todo al cerrar
    aengine.close();
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