#ifndef EXAGON_GAME_PROCESS_HPP
#define EXAGON_GAME_PROCESS_HPP

#include "../resource.h"
#include "utils/Color.h"
#include "Time.hpp"
#include "Songplayer.hpp"
#include "AnimationMaker.hpp"
#include "LeverLoader.hpp"
#include "CollisionSystem.hpp"
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
        //DATOS CARGADOS
        LevelData currentLevel;
 
        //Ratio
        float colorSwapRatio=1.5f;  //Cada cuantos segundos cambia de color
        //Cambio de color
        float hueFactor=0.2f;
        float hueSpeed=0.5f;
        //Timers                
        float timer1 = 0.0f;        //ColorSwap
        //Eventos que pueden ocurrir
        //Rotacion aleatoria
        //std::vector<float> randRotX = {0.0f, 0.5f, -0.5f};
        //std::vector<float> randRotY = {0.0f, 0.5f, -0.5f};
        //std::vector<float> randRotZ = {180.0f, -180.0f, 360.0f, -360.0f};
        //Tiempos de asignacion

        //=================================================================================//
        //VARIABLES PROPIAS DE LA CLASE
        //=====================================VISTA======================================//
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
        float deltaRotX = 0.0f;
        float deltaRotY = 0.0f;
        float deltaRotZ = -180.0f;
        //Colors
        std::vector<RGBColor> wallcolors={
            {0.255f, 0.863f, 1.0f},//ColC - Color principal del centro y la pared
            {0.2f, 0.749f, 0.871f}//Col2
        };  
        std::vector<RGBColor> pcolors={
            {0.102f, 0.376f, 0.86f},//Col1
            {0.196f, 0.576f, 0.922f},//Col2
            {0.071f, 0.267f, 0.612f}//,//ColO - El ultimo solo se renderiza cuando es impar
        };
        //==================================GAMEPLAY=======================================//
        //Variables de la partida==========================================================//
        //Poll
        RotSwitch rotMode;
        std::vector<float> pollRotX = {0.0f};
        std::vector<float> pollRotY = {0.0f};
        std::vector<float> pollRotZ = {0.0f};
        unsigned int ptrRotX = 0;
        unsigned int ptrRotY = 0;
        unsigned int ptrRotZ = 0;
        //PollTime
        std::vector<float> randIntervalR = {5.0f};
        //Obstaculos
        std::vector<ObsData>* obstacleData = nullptr;
        //Game
        //Cancion
        std::string SONG="levels/songs/Focus.mp3";
        bool GAME_ACTIVE=true;
        unsigned int SIDES= 3;
        //Ratio de aparacion de obstaculos
        const float WALLS_SPAWN_RATIO = 0.058f;
        //ID obstaculo
        unsigned int obsID = 0;
        //Jugador
        const float PLAYER_SENSIBILITY = 500.0f;
        //=================================================================================//
        //Punteros de funciones
        std::function<void(Animation*, float, unsigned int)>chsBG=std::bind(&ExagonGameProcess::changeDynamicSideBG, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        //Objetos de referencia
        Engine* GEnginePH;
        AudioEngine* AEnginePH;
        //Aqui nacen los objetos que quiera usar en el juego (usados apenas empezar)
        Shader Shader1;
        LeverLoader gameLevel;
        CollisionSystem colhandler;
        Obstacle obstacle;
        Timer gameTime;
        SongPlayer songPlayer;
        BG background;
        Center center;
        Player player;
        //Objetos usados prejuego (usados para cargar el nivel)
        //Timers
        cbChronometer* C1;    //Generacion de obstaculos
        Chronometer* T1;    //Cosas random
        Chronometer* T3;    //Obstaculos random
        //Punteros de animaciones
        //std::vector<Animation*> animations={};
        //Paredes
        std::vector<std::unique_ptr<CompleteWall>> completeWalls={};
        //CompleteWall* WallTest;
        //Animation* wa1;
        Animation* a1;
        Animation* a2;
        Animation* a3;
        Animation* a4;

        //Methods
        void linkLevel();
        void loadLevel();
        void startLevel();
        void handleEvents(float deltaTime);
        void switchObstacle();
        float chooseInPoll(std::vector<float>& poll, SwitchMode& mode, unsigned int& ptr);
        void spawnWallsByObstacle(float time);
        void changeDynamicSideBG(Animation* anim, float deltamov, unsigned int sides);
    public:
        //Constructor
        ExagonGameProcess(Engine* enginehere, AudioEngine* plhAEngine);
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
        std::vector<std::unique_ptr<CompleteWall>>& getWalls() {
            return completeWalls;
        }
        //Methods
        void PlayLevel();
};

ExagonGameProcess::ExagonGameProcess(Engine* plhEngine, AudioEngine* plhAEngine):
    GEnginePH(plhEngine),
    AEnginePH(plhAEngine),
    Shader1(IDR_VSHADER2,IDR_FSHADER2),
    gameLevel(),
    colhandler(),
    obstacle(),
    gameTime(),
    songPlayer(AEnginePH)//,
    //background(GEnginePH, &Shader1, 200.0f, sides, 3, pcolors),
    //center(GEnginePH, &Shader1, 0.18f, 0.018f, sides,7, pcolors, wallcolors.at(0)),
    //player(GEnginePH, &Shader1, PLAYER_SENSIBILITY, 2.0f, 0.21f, 60.0f, wallcolors.at(0))
{
    std::cout<<"Oh me creooo, dice el juego"<<std::endl;

    //Inicializacion del nivel
    //gameLevel.loadLevel("levels/vanilla/lvltest.txt");
    //obstacleData = gameLevel.getInfo();
    //gameLevel.printLevelInfo();

    //Perspectiva
    //background.setPerspective(FOV, nearD, farD);  
    //background.setCamera(CameraX, CameraY, CameraZ);

    //Timers
    C1=new cbChronometer(WALLS_SPAWN_RATIO);  //Paredes por defecto
    T1=new Chronometer(2.0f);   //Rotaciones
    //T2=new Chronometer(0.06f);  //Paredes por defecto
    //T3=new Chronometer(2.0f);   //Obstaculos
    //Animaciones aparte
    a1=new Animation(9, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a2=new Animation(5, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a3=new Animation(3, 1.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    a4=new Animation(6, 5.0f, 2.0f, chsBG, AnimType::BGEASEINOUT);
    //Preambulo
    //songPlayer.loadSong(song.c_str());
    //songPlayer.setupSong(0, 0.5f, 1.0f, true);
    //songPlayer.playSong();
    //gameTime.restart();
    loadLevel();
    startLevel();
}
ExagonGameProcess::~ExagonGameProcess(){
    delete a1;
    delete a2;
    delete a3;
    delete a4;
    delete C1;
    delete T1;
    //delete T3;
}
void ExagonGameProcess::PlayLevel(){
    if(GAME_ACTIVE){
        if(!player.isAlive()){
            GAME_ACTIVE = false;
            songPlayer.stopSong(); 
            return;
        } 

        float time = gameTime.getTime(); //Tiempo en general
        //std::cout<<time<<std::endl;
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
            T1->setTTime(randIntervalR.at(rand()%randIntervalR.size()));
            deltaRotX=chooseInPoll(pollRotX, rotMode.modeX, ptrRotX);
            deltaRotY=chooseInPoll(pollRotY, rotMode.modeY, ptrRotY);
            deltaRotZ=chooseInPoll(pollRotZ, rotMode.modeZ, ptrRotZ);
        }
        //Generacion de paredes
        spawnWallsByObstacle(time);
        //Movimiento de paredes
        for (auto ptr = completeWalls.begin(); ptr != completeWalls.end(); ) {
            (*ptr)->execute(dtime);
            if ((*ptr)->isAlive()==false) {
                ptr = completeWalls.erase(ptr);
            } else {
                ++ptr;
            }
        }
        //Colisiones
        colhandler.doCollisions(player, completeWalls);
        //Cambio de color
        if((time-timer1)>=colorSwapRatio){
            timer1=time;
            background.swapColors();
            //center.swapColors();
        }
        /*
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
        */
    }
}
//Transfiere datos al nivel
void ExagonGameProcess::loadLevel(){
    //En un futuro va ir un switch case para la seleccion de niveles
    gameLevel.loadLevel("levels/vanilla/lvltest2.txt");
    //obstacleData = gameLevel.getInfo();
    currentLevel = gameLevel.getLevelInfo();
    gameLevel.printLevelInfo();
    //Level linking
    linkLevel();
    background = BG(GEnginePH, &Shader1, 200.0f, SIDES, 3, pcolors);
    center = Center(GEnginePH, &Shader1, 0.18f, 0.018f, SIDES, 7, pcolors, wallcolors.at(0));
    player = Player(GEnginePH, &Shader1, PLAYER_SENSIBILITY, 2.0f, 0.21f, 60.0f, wallcolors.at(0));

    background.setPerspective(FOV, nearD, farD);  
    background.setCamera(CameraX, CameraY, CameraZ);
}
//Vincula metadatos
void ExagonGameProcess::linkLevel(){
    this->SONG=currentLevel.song;
    this->SIDES=currentLevel.phaseData[0].sides;
    this->pcolors=currentLevel.phaseData[0].mainColors;
    this->wallcolors=currentLevel.phaseData[0].wallColors;
    this->obstacleData=&currentLevel.phaseData[0].obs;
    this->randIntervalR=currentLevel.phaseData[0].pollTime;
    this->rotMode.modeX=currentLevel.phaseData[0].RotS.modeX;
    this->rotMode.modeY=currentLevel.phaseData[0].RotS.modeY;
    this->rotMode.modeZ=currentLevel.phaseData[0].RotS.modeZ;
    this->pollRotX=currentLevel.phaseData[0].pollDRot.pollRotX;
    this->pollRotY=currentLevel.phaseData[0].pollDRot.pollRotY;
    this->pollRotZ=currentLevel.phaseData[0].pollDRot.pollRotZ;
}
//Arranca un nivel antes de empezar
void ExagonGameProcess::startLevel(){
    //Elegir las variables iniciales
    deltaRotX=chooseInPoll(pollRotX, rotMode.modeX, ptrRotX);
    deltaRotY=chooseInPoll(pollRotY, rotMode.modeY, ptrRotY);
    deltaRotZ=chooseInPoll(pollRotZ, rotMode.modeZ, ptrRotZ);
    //Cargar la cancion
    songPlayer.loadSong(SONG.c_str());
    songPlayer.setupSong(0, 0.5f, 1.0f, true);
    songPlayer.playSong();
    gameTime.restart();
}
//Manejador de eventos
void ExagonGameProcess::handleEvents(float deltaTime){
    //Nivel - Jugador
    if(GEnginePH->getKey(262)){//Derecha
        float velocity = - PLAYER_SENSIBILITY * deltaTime;
        //std::cout<<"Se mueve a la derecha"<<std::endl;
        player.move(velocity);
    }
    if(GEnginePH->getKey(263)){//Izquierda
        float velocity = PLAYER_SENSIBILITY * deltaTime;
        //std::cout<<"Se mueve a la izquierda"<<std::endl;
        player.move(velocity);
    }
}
//Cambia un obstaculo de manera aleatoria
void ExagonGameProcess::switchObstacle(){
    if(!obstacleData->empty()){
        obstacle.restart();
        obsID=rand()%obstacleData->size();
    }
}
float ExagonGameProcess::chooseInPoll(std::vector<float>& poll, SwitchMode& mode, unsigned int& ptr){
    if(poll.empty()) return 0.0f;
    switch(mode){
        case SwitchMode::CYCLIC:{
            float out = poll.at(ptr%poll.size());
            ptr++;
            return out;
        }      
        case SwitchMode::RANDOM:
            return poll.at(rand()%poll.size());
        default: return 0.0f;          
    }
}
//Invoca una pared completa desde un obstaculo
void ExagonGameProcess::spawnWallsByObstacle(float time){
    if(C1->track(time)) {
        if(obstacleData->empty()) return;
        if(!obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).indexes.empty()){
            switch (obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).type){
                case AnimType::LINEAR:
                    completeWalls.emplace_back(std::make_unique<CompleteWall>
                        (GEnginePH, 
                        &Shader1, 
                        &center, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).duration, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).type, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).indexes, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginL, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginR, 
                        wallcolors, 4));
                    break;
                default:
                    completeWalls.emplace_back(std::make_unique<CompleteWall>
                        (GEnginePH, 
                        &Shader1, 
                        &center, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).duration,
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).factor,
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).type, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).indexes, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginL, 
                        obstacleData->at(obsID).anims.at(obstacle.getNoAnim()).wall.at(obstacle.getNoWall()).marginR, 
                        wallcolors, 4));
                    break;  
            }  
        }     
        obstacle.track(obstacleData, obsID);
        //Cambio de obstaculos
        if(obstacle.finished()) switchObstacle();
    }
}
//Cambia los lados de manera dinamica con morphing
void ExagonGameProcess::changeDynamicSideBG(Animation* anim, float deltamov, unsigned int sides){
    //std::cout<<deltamov<<std::endl;
    if(anim->Inited()){
        if(this->SIDES>sides){
            background.prepareBGforDecrease(sides);
            center.prepareCenterforDecrease(sides);
            //if(wt1) wt1->prepareWallforDecrease(sides);
            
        }else{
            background.prepareBGforIncrease(sides);
            center.prepareCenterforIncrease(sides);
            //if(wt1) wt1->prepareWallforIncrease(sides);
            this->SIDES=sides;
        }
    }
    background.softchangeSides(deltamov);
    if(this->SIDES>sides&&deltamov==1.0f){
        background.endUpdate(sides);
        center.endUpdate(sides);
        //if(wt1) wt1->endUpdate(sides);
        this->SIDES=sides;
    }
}
//Cambia los lados de manera brusca

#endif