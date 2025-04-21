#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "Color.h"
#include "Time.hpp"
#include "AnimationMaker.hpp"
#include "BG.hpp"

#include <iostream>
#include <functional>

class ExagonGameProcess {
    private:
        //Una prueba de valores como si los estuviera pasando desde otro programa
        //Escenario
        unsigned int sides=6;
        //Ratio
        float colorSwapRatio=1.5f;  //Cada cuantos segundos cambia de color
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
        float deltaRotX=0.0f;
        float deltaRotY=0.0f;
        float deltaRotZ=-180.0f;    //El que mas nos interesa
        //Timers                
        float timer1 = 0.0f;        //ColorSwap
        float timer2 = 0.0f;
        //Colores
        std::vector<RGBColor> wallcolors={
            {0.255f, 0.863f, 1.0f},//ColC - Color principal del centro y la pared
            {0.2, 0.749, 0.871}//Col2
        };      
        std::vector<RGBColor> pcolors={
            {0.196f, 0.576f, 0.922f},//Col1
            {0.102f, 0.376f, 0.86f},//Col2
            {0.071f, 0.267f, 0.612f}//,//ColO - El ultimo solo se renderiza cuando es impar
        };
        //Variables propias de la clase
        //Punteros de funciones
        std::function<void(Animation*, float, int)>chsBG=std::bind(&ExagonGameProcess::changeDynamicSideBG, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        //Objetos de referencia
        Engine* EnginePlaceHolder;
        //Aqui nacen los objetos que quiera usar en el juego
        Timer gameTime;
        BG background;
        //Punteros de animaciones
        std::vector<Animation*> animations={};
        Animation* a1;
        Animation* a2;

        //Methods
        void changeDynamicSideBG(Animation* anim, float deltamov, int sides);
    public:
        //Constructor
        ExagonGameProcess(Engine* enginehere);
        ~ExagonGameProcess();
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
    background(EnginePlaceHolder, 0.9f,sides,3,pcolors,Type::CLASSIC)
{
    std::cout<<"Oh me creooo, dice el juego"<<std::endl;
    //Inicializacion del nivel
    background.setPerspective(FOV, nearD, farD);  
    background.setCamera(CameraX, CameraY, CameraZ);
    background.setScale(scale);
    //a1=new Animation(3, 2.0f, chsBG, AnimType::BGLINEAR);
    a1=new Animation(3, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a2=new Animation(5, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
}
ExagonGameProcess::~ExagonGameProcess(){
    delete a1;
    delete a2;
}
void ExagonGameProcess::PlayLevel(){
    float time = gameTime.getTime(); //Tiempo en general
    float dtime = gameTime.getDeltaTime();
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
    //Test Timeline
    if(time>=11.0f){
        a1->execute(dtime); 
    }
    if(time>=16.0f){
        a2->execute(dtime);
    }     
}
//Cambia los lados de manera dinamica con morphing
void ExagonGameProcess::changeDynamicSideBG(Animation* anim, float deltamov, int sides){
    std::cout<<deltamov<<std::endl;
    if(anim->Inited()){
        if(this->sides>sides){
            background.prepareBGforDecrease(sides);
        }else{
            background.prepareBGforIncrease(sides);
            this->sides=sides;
        }
    }
    background.softchangeSides(deltamov);
    if(this->sides>sides&&deltamov==1.0f){
        background.endUpdate(deltamov);
        this->sides=sides;
    }
}
//Cambia los lados de manera brusca

//Para es escalado y movimiento

#endif