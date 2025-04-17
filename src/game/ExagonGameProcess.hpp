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
        float hueFactor=0.2f;
        float hueSpeed=0.5f;
        float timer1 = 0.0f;
        std::vector<RGBColor> pcolors={
            {0.196f, 0.576f, 0.922f},//Col1
            {0.102f, 0.376f, 0.86f},//Col2
            {0.071f, 0.267f, 0.612f}//,//ColO
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
    background.changeBGHue(time, hueFactor, hueSpeed);
    if((time-timer1)>=colorSwapRatio){
        timer1=time;
        background.swapColors();
        //std::cout<<"Cambio de color"<<std::endl;
    }
    
}

#endif