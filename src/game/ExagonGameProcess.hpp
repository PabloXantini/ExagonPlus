#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include <glm/glm.hpp>

#include "Color.h"
#include "BGType.hpp"
#include "BG.hpp"

#include <iostream>

class ExagonGameProcess {
    private:
        //Una prueba de colores como si los estuviera pasando desde otro programa
        float colorSwapRatio=1.5f;
        float timer1 = 0.0f;
        std::vector<RGBColor> pcolors={
            {1.0f,0.0f,0.0f},//Rojo
            {0.0f,1.0f,0.0f},//Verde
            {0.0f,0.0f,1.0f}//,//Azul
            //{1.0f,1.0f,0.0f}//El ultimo solo se renderiza cuando es impar
        };
        //Objetos de referencia
        Engine* EnginePlaceHolder;
        //Aqui nacen los objetos que quiera usar en el juego
        BG background;
    public:
        //Constructor
        ExagonGameProcess(Engine* enginehere);
        //Getters   
        BG& getBG() {
            return background;
        }
        //Methods
        void PlayLevel();
};

ExagonGameProcess::ExagonGameProcess(Engine* plhEngine):
    EnginePlaceHolder(plhEngine),
    background(EnginePlaceHolder, 0.9f,6,3,pcolors,Type::CLASSIC)
{
    std::cout<<"Oh me creooo, dice el juego"<<std::endl;
}

void ExagonGameProcess::PlayLevel(){
    float time = glfwGetTime(); //Tiempo en general
    //std::cout<<time<<std::endl;
    if((time-timer1)>=colorSwapRatio){
        timer1=time;
        background.swapColors();
        std::cout<<"Cambio de color"<<std::endl;
    }
    
}

#endif