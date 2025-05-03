#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "../resource.h"
#include "utils/Color.h"
#include "Time.hpp"
#include "Songplayer.hpp"
#include "AnimationMaker.hpp"
#include "LeverLoader.hpp"
#include "BG.hpp"
#include "Center.hpp"
#include "WallObject.hpp"
#include "Wall.hpp"
#include "Player.hpp"

#include <iostream>
#include <functional>
#include <string>
#include <cstdlib>

class ExagonGameProcess {
    private:
        //=======================================================================
        //Una prueba de valores como si los estuviera pasando desde otro programa
        //Cancion
        std::string song="levels/songs/Focus.mp3"; 
        //DATOS CARGADOS
        std::vector<ObsData> obstacleData ={};
        //Escenario
        unsigned int sides=5;
        //Ratio
        float colorSwapRatio=1.5f;  //Cada cuantos segundos cambia de color
        //Cambio de color
        float hueFactor=0.2f;
        float hueSpeed=0.5f;
        //Perspectiva
        float nearD=0.1f;
        float farD=500.f;
        float FOV=45.0f;
        //Camara
        float CameraX = 0.0f;
        float CameraY = 0.0f;
        float CameraZ = 2.0f;
        //Transformaciones
        float scale = 1.0f;
        float deltaRotX=2.0f;
        float deltaRotY=2.0f;
        float deltaRotZ=-180.0f;    //El que mas nos interesa
        //Timers                
        float timer1 = 0.0f;        //ColorSwap
        //Colores
        std::vector<RGBColor> wallcolors={
            {0.255f, 0.863f, 1.0f},//ColC - Color principal del centro y la pared
            {0.2f, 0.749f, 0.871f}//Col2
        }; 
        std::vector<RGBColor> ccolors={
            {0.102f, 0.376f, 0.86f}
        };     
        std::vector<RGBColor> pcolors={
            {0.102f, 0.376f, 0.86f},//Col1
            {0.196f, 0.576f, 0.922f},//Col2
            {0.071f, 0.267f, 0.612f}//,//ColO - El ultimo solo se renderiza cuando es impar
        };
        //Eventos que pueden ocurrir
        //Rotacion aleatoria
        std::vector<float> randRotX = {0.0f};
        std::vector<float> randRotY = {0.0f};
        std::vector<float> randRotZ = {180.0f, -180.0f, 360.0f, -360.0f};
        //Tiempos de asignacion
        std::vector<float> randInterval = {5.0f, 7.0f, 6.0f};
        std::vector<float> randIntervalObs = {4.0f, 3.0f, 5.0f};
        //=================================================================================//
        //Variables propias de la clase
        //ID obstaculo
        unsigned int obsID = 0;
        //Jugador
        const float PLAYER_SENSIBILITY = 500.0f;
        //Punteros de funciones
        std::function<void(Animation*, float, unsigned int)>chsBG=std::bind(&ExagonGameProcess::changeDynamicSideBG, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        //Objetos de referencia
        Engine* EnginePlaceHolder;
        //Aqui nacen los objetos que quiera usar en el juego (usados apenas empezar)
        Shader Shader1;
        LeverLoader gameLevel;
        Obstacle obstacle;
        Timer gameTime;
        SongPlayer songPlayer;
        BG background;
        Center center;
        Player player;
        //Objetos usados prejuego (usados para cargar el nivel)
        //Timers
        Chronometer* T1;    //Cosas random
        Chronometer* T2;    //Generacion de obstaculos
        Chronometer* T3;    //Obstaculos random
        //Punteros de animaciones
        //std::vector<Animation*> animations={};
        //Paredes
        //std::vector<CompleteWall*> completeWalls={};
        std::vector<CompleteWall*> completeWalls={};
        std::vector<unsigned int> WTIndexes = {0,2,4};
        //CompleteWall* WallTest;
        //Animation* wa1;
        Animation* a1;
        Animation* a2;
        Animation* a3;
        Animation* a4;

        //Methods
        void handleEvents(float deltaTime);
        void changeDynamicSideBG(Animation* anim, float deltamov, unsigned int sides);
    public:
        //Constructor
        ExagonGameProcess(Engine* enginehere);
        ~ExagonGameProcess();
        //Getters   
        BG& getBG() {
            return background;
        }
        Center& getCenter() {
            return center;
        }
        Player& getPlayer() {
            return player;
        }
        std::vector<CompleteWall*>& getWalls() {
            return completeWalls;
        }
        //Methods
        void PlayLevel();
};

ExagonGameProcess::ExagonGameProcess(Engine* plhEngine):
    EnginePlaceHolder(plhEngine),
    Shader1(IDR_VSHADER2,IDR_FSHADER2),
    gameLevel(),
    obstacle(),
    gameTime(),
    songPlayer(),
    background(EnginePlaceHolder, &Shader1, 200.0f, sides, 3, pcolors),
    center(EnginePlaceHolder, &Shader1, 0.18f, 0.018f, sides,7, pcolors, wallcolors.at(0)),
    player(EnginePlaceHolder, &Shader1, PLAYER_SENSIBILITY, 2.0f, 0.21f, 60.0f, wallcolors.at(0))
{
    std::cout<<"Oh me creooo, dice el juego"<<std::endl;
    //Inicializacion del nivel
    gameLevel.loadLevel("levels/vanilla/lvl1.txt");
    obstacleData = gameLevel.getInfo();
    gameLevel.printInfo();
    //Perspectiva
    background.setPerspective(FOV, nearD, farD);  
    background.setCamera(CameraX, CameraY, CameraZ);
    //Timers
    T1=new Chronometer(2.0f);   //Rotaciones
    T2=new Chronometer(0.06f);  //Paredes por defecto
    T3=new Chronometer(2.0f);   //Obstaculos
    //Paredes?
    //WallTest=new CompleteWall(EnginePlaceHolder, &Shader1, &center, 1.0f, AnimType::LINEAR, WTIndexes, 0.1f, 0.1f, wallcolors, 4);
    //Animaciones aparte
    a1=new Animation(9, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a2=new Animation(5, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a3=new Animation(3, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a4=new Animation(6, 5.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
}
ExagonGameProcess::~ExagonGameProcess(){
    delete a1;
    delete a2;
    delete a3;
    delete a4;
    delete T1;
    delete T2;
    delete T3;
}
void ExagonGameProcess::PlayLevel(){
    //songPlayer.playSong(song);
    float time = gameTime.getTime(); //Tiempo en general
    float dtime = gameTime.getDeltaTime();
    //Eventos
    handleEvents(dtime);
    //Cosas que se hacen siempre
    background.changeBGHue(time, hueFactor, hueSpeed);
    background.rotateBG(dtime, deltaRotX, deltaRotY, deltaRotZ);
    //Cosas de pared
    //WallTest->execute(dtime);

    //Cambio de parametros
    if(T1->track(time)) {
        T1->setTTime(randInterval.at(rand()%randInterval.size()));
        deltaRotX=randRotX.at(rand()%randRotX.size());
        deltaRotY=randRotY.at(rand()%randRotY.size());
        deltaRotZ=randRotZ.at(rand()%randRotZ.size());
    }
    if(T3->track(time)) {
        if(!obstacleData.empty()){
            T3->setTTime(randIntervalObs.at(rand()%randIntervalObs.size()));
            obstacle.restart();
            obsID=rand()%obstacleData.size();
        } 
    }
    //Generacion de paredes
    if(T2->track(time)) {
        if(!obstacleData.empty()){
            if(!obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).indexes.empty()){
                switch (obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).type){
                    case AnimType::LINEAR:
                        completeWalls.push_back(new CompleteWall
                            (EnginePlaceHolder, 
                            &Shader1, 
                            &center, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).duration, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).type, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).indexes, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginL, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginR, 
                            wallcolors, 4));
                        break;
                    default:
                        completeWalls.push_back(new CompleteWall
                            (EnginePlaceHolder, 
                            &Shader1, 
                            &center, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).duration,
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).factor,
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).type, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).indexes, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginL, 
                            obstacleData.at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginR, 
                            wallcolors, 4));
                        break;  
                }  
            }     
            obstacle.track(obstacleData, obsID);
        }
    }
    //Movimiento de paredes
    /*
    for(CompleteWall& wall : this->completeWalls){
        wall.execute(dtime);
    }
    this->completeWalls.erase(std::remove_if(this->completeWalls.begin(), this->completeWalls.end(),
        [](CompleteWall &wall) { return wall.isAlive()==false; }
    ), this->completeWalls.end());
    */
    for (auto ptr = completeWalls.begin(); ptr != completeWalls.end(); ) {
        CompleteWall* wall = *ptr;
        if (wall != nullptr) {
            wall->execute(dtime);
            if (wall->isAlive()==false) {
                delete wall;
                ptr = completeWalls.erase(ptr);
            } else {
                ++ptr;
            }
        } else {
            ptr = completeWalls.erase(ptr);
        }
    }
    //Cambio de color
    if((time-timer1)>=colorSwapRatio){
        timer1=time;
        background.swapColors();
        //center.swapColors();
    }
    //Test Timeline
    if(time>=8.0f){
        a1->execute(dtime); 
    }
    if(time>=11.0f){
        a2->execute(dtime);
    }
    if(time>=14.0f){
        a3->execute(dtime);
    }
    if(time>=17.0f){
        a4->execute(dtime);
    }
}
//Event handler - A decidir como va a quedar
void ExagonGameProcess::handleEvents(float deltaTime){
    //Nivel - Jugador
    if(EnginePlaceHolder->getKey(262)){//Derecha
        float velocity = - PLAYER_SENSIBILITY * deltaTime;
        //std::cout<<"Se mueve a la derecha"<<std::endl;
        player.move(velocity);
    }
    if(EnginePlaceHolder->getKey(263)){//Izquierda
        float velocity = PLAYER_SENSIBILITY * deltaTime;
        //std::cout<<"Se mueve a la izquierda"<<std::endl;
        player.move(velocity);
    }
}

//Cambia los lados de manera dinamica con morphing
void ExagonGameProcess::changeDynamicSideBG(Animation* anim, float deltamov, unsigned int sides){
    //std::cout<<deltamov<<std::endl;
    if(anim->Inited()){
        if(this->sides>sides){
            background.prepareBGforDecrease(sides);
            center.prepareCenterforDecrease(sides);
            //if(wt1) wt1->prepareWallforDecrease(sides);
            
        }else{
            background.prepareBGforIncrease(sides);
            center.prepareCenterforIncrease(sides);
            //if(wt1) wt1->prepareWallforIncrease(sides);
            this->sides=sides;
        }
    }
    background.softchangeSides(deltamov);
    if(this->sides>sides&&deltamov==1.0f){
        background.endUpdate(sides);
        center.endUpdate(sides);
        //if(wt1) wt1->endUpdate(sides);
        this->sides=sides;
    }
}
//Cambia los lados de manera brusca

#endif