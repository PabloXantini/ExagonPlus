#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "Color.h"
#include "BGType.hpp"
#include "BG.hpp"

class ExagonGameProcess {
    private:
        //Una prueba de colores como si los estuviera pasando desde otro programa
        std::vector<RGBColor> pcolors={
            {1.0f,0.0f,0.0f},//Rojo
            {0.0f,1.0f,0.0f},//Verde
            {0.0f,0.0f,1.0f}//,//Azul
            //{1.0f,1.0f,0.0f}//Amarillo
        };
        //Objetos de referencia
        Engine& EnginePlaceHolder;
        //Aqui nacen los objetos que quiera usar en el juego
        BG background;
    public:
        //Constructor
        ExagonGameProcess(Engine& enginehere);
        //Getters   
        BG& getBG() {
            return background;
        }
};

ExagonGameProcess::ExagonGameProcess(Engine& plhEngine):
    EnginePlaceHolder(plhEngine),
    background(plhEngine, 0.9f,6,pcolors,Type::CLASSIC)
    {

    }

#endif