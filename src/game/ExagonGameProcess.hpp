#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "Color.h"
#include "Time.hpp"
#include "BGType.hpp"
#include "BG.hpp"

#include <iostream>

class ExagonGameProcess {
    private:
        //Una prueba de valores como si los estuviera pasando desde otro programa
        //Duraciones
        float colorSwapRatio=1.5f;  //Cada cuantos segundos cambia de color

        float scaleDuration1=3.0f;

        //Cambio de color
        float hueFactor=0.2f;
        float hueSpeed=0.5f;
        //Perspectiva
        float nearD=0.1f;
        float farD=100.f;
        float FOV=45.0f;
        //Camara
        float CameraX = 0.0f;
        float CameraY = 0.0f;
        float CameraZ = 2.0f;
        //Transformaciones
        float scale = 1.0f;
        float deltaRotX=5.0f;
        float deltaRotY=5.0f;
        float deltaRotZ=-180.0f;    //El que mas nos interesa
        //Timers                
        float timer1 = 0.0f;        //ColorSwap
        float timer2 = 0.0f;        
        std::vector<RGBColor> pcolors={
            {0.196f, 0.576f, 0.922f},//Col1
            {0.102f, 0.376f, 0.86f},//Col2
            {0.071f, 0.267f, 0.612f}//,//ColO
            //{1.0f,1.0f,0.0f}//El ultimo solo se renderiza cuando es impar
        };
        enum moveFunction {
            LINEAR,
            EASEIN,
            EASEOUT,
            EXPONENTIAL
        };
        //Objetos de referencia
        Engine* EnginePlaceHolder;
        //Aqui nacen los objetos que quiera usar en el juego
        Timer gameTime;
        BG background;
        void changeDynamicSideBG(float time, int sides, float duration, moveFunction movetype);
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
    gameTime(),
    background(EnginePlaceHolder, 0.9f,6,3,pcolors,Type::CLASSIC)
{
    std::cout<<"Oh me creooo, dice el juego"<<std::endl;
    background.setPerspective(FOV, nearD, farD);  
    background.setCamera(CameraX, CameraY, CameraZ);
    background.setScale(scale);
}

void ExagonGameProcess::PlayLevel(){
    float time = gameTime.getTime(); //Tiempo en general
    timer2 = time;
    //std::cout<<time<<std::endl;
    //Cosas que se hacen siempre
    background.changeBGHue(time, hueFactor, hueSpeed);
    background.rotateBG(time, deltaRotX, deltaRotY, deltaRotZ);
    if((time-timer1)>=colorSwapRatio){
        timer1=time;
        background.swapColors();
        //std::cout<<"Cambio de color"<<std::endl;
    }
        
}

void ExagonGameProcess::changeDynamicSideBG(float time, int sides, float duration, moveFunction movetype){
    std::cout<<time<<std::endl;
    switch (movetype){
        case LINEAR:

            break;
    }
}
//Para el escenario
float moveLinear(float time, float duration){
    return 1.0f;
}
//Para es escalado y movimiento

#endif