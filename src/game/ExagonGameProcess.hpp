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
        //Aqui nacen los objetos que quiera usar en el juego
        BG background;
    public:
        //Constructor
        ExagonGameProcess();
        //Getters   
        BG& getBG() {
            return background;
        }
};

ExagonGameProcess::ExagonGameProcess():
    background(0.9f,6,pcolors,Type::CLASSIC)
    {

    }

#endif