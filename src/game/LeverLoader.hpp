#ifndef LEVER_LOADER_HPP
#define LEVER_LOADER_HPP

#include "AnimationMaker.hpp"
#include "utils/Color.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

enum class SwitchMode {
    CYCLIC,
    RANDOM,
    UNKNOWN
};
enum class SwitchSubMode {
    PROBABILISTIC,
    INTERVAL,
    UNKNOWN
};
enum class Func {
    FUNC1,
    FUNC2,
    UNKNOWN
};
struct RotSwitch {
    SwitchMode modeX = SwitchMode::RANDOM;
    SwitchMode modeY = SwitchMode::RANDOM;
    SwitchMode modeZ = SwitchMode::RANDOM;
};
struct PollSwitch {
    SwitchMode mode = SwitchMode::RANDOM;
    SwitchSubMode submode = SwitchSubMode::PROBABILISTIC;
    //Aplicable en PROBABILISTIC
    unsigned int PWeight = 0;
    //Aplicable en INTERVAL
    unsigned int pad = 0; 
};
struct AnimData {
    AnimType type;
    float duration;
    float factor;
    Func func;
    //Lados
    unsigned int arg1 = 0;
    //Escalado/Rotacion
    float arg2 = 0.0f;
};
struct AnimSequence {
    std::vector<AnimData> animations;
};
struct Event {
    float timestamp = 0;
    AnimData animation;
};
struct PollRot {
    std::vector<float> pollRotX;
    std::vector<float> pollRotY;
    std::vector<float> pollRotZ;
};
struct WallData {
    float marginL = 0.0f;
    float marginR = 0.0f;
    std::vector<unsigned int> indexes; 
};
struct AnimWallData {
    AnimType type;
    float duration;
    float factor;
    std::vector<WallData> wall;
};
struct ObsData {
    std::vector<AnimWallData> anims;
};
struct PhaseData {
    //Config
    unsigned int PhaseID = 0;
    unsigned int sides = 0;
    bool RythmPulsing = false;
    RotSwitch RotS;
    PollSwitch BGConfig;
    PollSwitch CamConfig;
    //Maincolors - Colores
    std::vector<RGBColor> mainColors={};
    //WallColors - Colores de pared
    std::vector<RGBColor> wallColors={};
    //PollTime - Intervalos aleatorios de tiempo para transformaciones
    std::vector<float> pollTime={};
    //PollDRot
    PollRot pollDRot={};
    //PollAnim para BG
    std::vector<AnimData> BGAnimations={};
    //PollAnim para Camara
    std::vector<AnimSequence> CamAnimations={};
    //Events
    std::vector<Event> events={};

    //Obstaculos
    std::vector<ObsData> obs={};
};
struct Phase {
    unsigned int PhaseID = 0;
    float timestamp = 0.0f;
};

class Obstacle {
    private:
        //bool MF=true;                 //Si necesita renderizar mas fragmentos

        bool DF=false;                  //Si no necesita renderizar nada
        unsigned int cwallpointer=0;    //Guardo la posicion de la wall en cuestion
        unsigned int canimpointer=0;    //Guardo la posicion de la animacion en cuestion
    public:
        Obstacle()=default;
        //Getters
        int getNoWall(){
            return cwallpointer;
        }
        unsigned int getNoAnim(){
            return canimpointer;
        }
        bool finished(){
            return DF;
        }
        void track(std::vector<ObsData>& obstacles, unsigned int ID){
            if(obstacles.empty()) return;
            cwallpointer++;
            if(cwallpointer>=obstacles.at(ID).anims.at(canimpointer).wall.size()-1){
                cwallpointer=0;
                canimpointer++;
                if(canimpointer>=obstacles.at(ID).anims.size()-1){
                    DF=true;
                    canimpointer=0;
                }
            }
        }
        void restart(){
            cwallpointer=0;
            canimpointer=0;
            DF=false;
        }
};

class LeverLoader {
    private:

        std::vector<ObsData> obs={};
        std::vector<RGBColor> wallColors={};
        enum State {
            NONE,
            WALLCOLORS,
            OBS,
            ANIM,
            WALL
        } state = NONE;
        //Methods
        //Metodos para parsing
        AnimType parseAnimType(const std::string& typeStr) {
            if (typeStr == "LINEAR") return AnimType::LINEAR;
            if (typeStr == "EASEINOUT") return AnimType::EASEINOUT;
            return AnimType::UNKNOWN;
        }
        SwitchMode parseSwitchMode(const std::string& typeStr){
            if(typeStr == "RANDOM") return SwitchMode::RANDOM;
            if(typeStr == "CYCLIC") return SwitchMode::CYCLIC;
            return SwitchMode::UNKNOWN;
        }
        SwitchSubMode parseSwitchSubMode(const std::string& typeStr){
            if(typeStr == "PROBABILISTIC") return SwitchSubMode::PROBABILISTIC;
            if(typeStr == "INTERVAL") return SwitchSubMode::INTERVAL;
            return SwitchSubMode::UNKNOWN;
        }
        Func parseFunc(const std::string& typeStr){
            if (typeStr == "SOFTCHANGESIDE") return Func::FUNC1;
            return Func::UNKNOWN;
        }
    public:
        LeverLoader()=default;
        const std::vector<ObsData>& getInfo() const{
            return obs;
        }
        /*
            Carga datos de un txt
        */
        void loadLevel(const char* filepath){
            obs.clear();
            ObsData currentObs;
            AnimWallData currentAnim;
            WallData currentWall;
            //Cosas de archivos
            std::string line;
            std::ifstream fstream(filepath);
            //Lee el archivo
            if(fstream){
                while(std::getline(fstream, line)){
                    if(line.empty()) continue;
                    std::istringstream sstream(line);
                    if(line=="WALLCOLORS"){
                        state = WALLCOLORS;
                        continue;
                    }
                    if(line=="OBS") {
                        currentObs={};
                        state = OBS;
                        continue;
                    }
                    if(line=="ANIM"){
                        currentAnim={};
                        state = ANIM;
                        continue;
                    }
                    if(line=="WALLDATA"){
                        currentWall={};
                        state = WALL;
                        continue;
                    }
                    if(line=="ENDWALLDATA"){
                        state = ANIM;
                        continue;
                    }
                    if (line=="ENDANIM"){
                        currentObs.anims.push_back(currentAnim);
                        state = OBS;
                        continue;
                    }
                    if (line=="ENDOBS"){
                        obs.push_back(currentObs);
                        state = NONE;
                        continue;
                    }
                    if(state == WALLCOLORS){
                        RGBColor color;
                        sstream >> color.R >> color.G >> color.B;
                        wallColors.push_back(color);
                    }else if(state == ANIM){
                        std::string type;
                        sstream >> currentAnim.duration >> type >> currentAnim.factor;
                        currentAnim.type = parseAnimType(type);
                    }else if(state == WALL){
                        std::string token;
                        sstream >> token;
                        if(token=="X"){
                            unsigned int count = 1;
                            sstream >> count;
                            WallData emptyWall;
                            for(int i=0; i<count; i++){
                                currentAnim.wall.push_back(emptyWall);
                            }
                        }else{
                            //Limpiar el buffer antes de hacer algo mas
                            sstream.clear();               // Asegura que el stringstream esté limpio
                            sstream.str(line);             // Reinicia con la línea completa
                            //Paredes
                            currentWall={};
                            std::vector<float> tokens;
                            float value;
                            while (sstream >> value) {
                                tokens.push_back(value);
                            }
                            if (tokens.size() >= 2) {
                                currentWall.marginL = tokens[tokens.size()-2];
                                currentWall.marginR = tokens[tokens.size()-1];
                                for (size_t i = 0; i < tokens.size()-2; ++i) {
                                    currentWall.indexes.push_back(static_cast<unsigned int>(tokens[i]));
                                }
                            }
                            currentAnim.wall.push_back(currentWall);
                        }
                    }
                }
            }
            fstream.close();
        }
        void printInfo(){
            // Mostrar resultados
            std::cout << "--- Wall Colors ---\n";
            for (auto& color : wallColors) {
                std::cout << color.R << " " << color.G << " " << color.B << "\n";
            }
            std::cout << "\n--- Obstacles ---\n";
            for (size_t i = 0; i < obs.size(); ++i) {
                std::cout << "Obstacle #" << i << "\n";
                for (size_t j = 0; j < obs[i].anims.size(); ++j) {
                    std::cout << "  Anim #" << j 
                            << " (Type: " << static_cast<int>(obs[i].anims[j].type) 
                            << ", Duration: " << obs[i].anims[j].duration 
                            << ", Factor: " << obs[i].anims[j].factor << ")\n";
                    for (auto& wall : obs[i].anims[j].wall) {
                        std::cout << "    Indexes:";
                        if (wall.indexes.empty()) {
                            std::cout << " (vacío)";
                        } else {
                            for (auto idx : wall.indexes) {
                                std::cout << " " << idx;
                            }
                        }
                        std::cout << " | marginL: " << wall.marginL << ", marginR: " << wall.marginR << "\n";
                    }
                }
            }
        }
};

#endif