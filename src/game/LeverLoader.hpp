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
    FUNC3,
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
    AnimType type = AnimType::UNKNOWN;
    float duration;
    float factor;
    Func func = Func::UNKNOWN;
    //Lados
    unsigned int f1arg1 = 0;
    //Escalado/Rotacion
    float f2arg1 = 0.0f;
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
//Estructura final
struct LevelData {
    std::string song;
    std::vector<Phase> phases={};
    std::vector<PhaseData> phaseData={};
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
        std::string song;
        std::vector<Phase> phases={};
        std::vector<PhaseData> phaseData={};
        //Paquete final
        LevelData level;
        //Version anterior
        std::vector<ObsData> obs={};
        std::vector<RGBColor> wallColors={};
        enum State {
            NONE,
            SONG,
            LEVEL_SEQ,
            PHASE,
            CONFIG,
            MAINCOLORS,
            WALLCOLORS,
            POLLTIME,
            POLLROT,
            POLLANIM,
            EVENTS,
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
        void readColor(std::istringstream sstream){
            RGBColor color;
            sstream >> color.R >> color.G >> color.B;
            wallColors.push_back(color);
        }
        std::string showMode(SwitchMode mode){
            switch(mode){
                case SwitchMode::CYCLIC: return "CYCLIC";
                case SwitchMode::RANDOM: return "RANDOM";
                case SwitchMode::UNKNOWN: return "UNKNOWN";
                default: return "INVALID";
            }
        }
        std::string showSubMode(SwitchSubMode submode){
            switch(submode){
                case SwitchSubMode::PROBABILISTIC: return "CYCLIC";
                case SwitchSubMode::INTERVAL: return "RANDOM";
                case SwitchSubMode::UNKNOWN: return "UNKNOWN";
                default: return "INVALID";
            }
        }
        std::string showFunc(Func func){
            switch(func){
                case Func::FUNC1: return "FUNC1";
                case Func::FUNC2: return "FUNC2";
                case Func::UNKNOWN: return "UNKNOWN";
                default: return "INVALID";
            }
        }
        std::string showAnimType(AnimType AnimType){
            switch(AnimType){
                case AnimType::LINEAR: return "LINEAR";
                case AnimType::EASEIN: return "EASEIN";
                case AnimType::EASEOUT: return "EASEOUT";
                case AnimType::EASEINOUT: return "EASEINOUT";
                case AnimType::UNKNOWN: return "UNKNOWN";
                default: return "INVALID";
            }
        }
        void printPhase(Phase& phase){
            std::cout<<"P: "<<phase.PhaseID<<"\tT: "<<phase.timestamp<<"\n";
        }
        void printPhaseID(PhaseData& phaseData){
            std::cout<<"PID: "<<phaseData.PhaseID<<"\n";
        }
        void printPhaseConfig(PhaseData& phaseData){
            std::cout<<"Intial Sides: "<<phaseData.sides<<"\n";
            std::cout<<"Rythm Pulsing: "<<std::boolalpha<<phaseData.RythmPulsing<<"\n";
            std::cout<<"PollSwitching RotX: "<<showMode(phaseData.RotS.modeX)<<"\n";
            std::cout<<"PollSwitching RotY: "<<showMode(phaseData.RotS.modeY)<<"\n";
            std::cout<<"PollSwitching RotZ: "<<showMode(phaseData.RotS.modeZ)<<"\n";
            SwitchSubMode BGSubMode = phaseData.BGConfig.submode;
            switch(BGSubMode){
                case SwitchSubMode::PROBABILISTIC:
                    std::cout<<"PollSwitching BG: "<<showMode(phaseData.BGConfig.mode)<<" "<<showSubMode(BGSubMode)<<" "<<phaseData.BGConfig.PWeight<<"\n";
                    break;
                case SwitchSubMode::INTERVAL:
                    std::cout<<"PollSwitching BG: "<<showMode(phaseData.BGConfig.mode)<<" "<<showSubMode(BGSubMode)<<" "<<phaseData.BGConfig.pad<<"\n";
                    break;
                default:
                    std::cout<<"PollSwitching BG: "<<showMode(phaseData.BGConfig.mode)<<" "<<showSubMode(BGSubMode)<<"\n";
                    break;
            }
            SwitchSubMode CamSubMode = phaseData.CamConfig.submode;
            switch(CamSubMode){
                case SwitchSubMode::PROBABILISTIC:
                    std::cout<<"PollSwitching BG: "<<showMode(phaseData.CamConfig.mode)<<" "<<showSubMode(CamSubMode)<<" "<<phaseData.BGConfig.PWeight<<"\n";
                    break;
                case SwitchSubMode::INTERVAL:
                    std::cout<<"PollSwitching BG: "<<showMode(phaseData.CamConfig.mode)<<" "<<showSubMode(CamSubMode)<<" "<<phaseData.BGConfig.pad<<"\n";
                    break;
                default:
                    std::cout<<"PollSwitching BG: "<<showMode(phaseData.CamConfig.mode)<<" "<<showSubMode(CamSubMode)<<"\n";
                    break;
            }
        }
        void printColor(RGBColor& color){
            std::cout<<"Color: "<<color.R <<" "<<color.G <<" "<<color.B<<"\n";
        }
        void printList(std::vector<float>& list){
            if(list.empty()){
                std::cout<<"(vacío)";
                return;
            }
            for(auto& element : list){
                std::cout<<element<<" ";
            }
        }
        void printList(std::vector<unsigned int>& list){
            if(list.empty()){
                std::cout<<"(vacío)";
                return;
            }
            for(auto& element : list){
                std::cout<<element<<" ";
            }
        }
        void printCWall(WallData& wall){
            printList(wall.indexes);
            std::cout<<" | marginL: "<<wall.marginL<<"\tmarginR: "<<wall.marginR<<"\n";
        }
        void printAnimW(AnimWallData& anim){
            AnimType type = anim.type;
            switch(type){
                case AnimType::LINEAR:
                    std::cout<<"Animation: duration-> "<<anim.duration<<"\ttype-> "<<showAnimType(type)<<"\n";
                    break;
                case AnimType::UNKNOWN:
                    std::cout<<"Animation: "<<showAnimType(type)<<"\n";
                    break;
                default:
                    std::cout<<"Animation: duration-> "<<anim.duration<<"\ttype-> "<<showAnimType(type)<<"\tf-> "<<anim.factor<<"\n";
                    break;
            }
        }
        void printAnimEvent(AnimData& animEvent){
            Func func = animEvent.func;
            AnimType type = animEvent.type;
            switch(func){
                case Func::FUNC1:
                    std::cout<<"FunctionAction: "<<showFunc(animEvent.func)<<"\targs: "<<animEvent.f1arg1<<"\n";
                    break;
                case Func::FUNC2:
                    std::cout<<"FunctionAction: "<<showFunc(animEvent.func)<<"\targs: "<<animEvent.f2arg1<<"\n";
                    break;
                default:
                    std::cout<<"FunctionAction: "<<showFunc(animEvent.func)<<" <-Funcion invalida\n";
                    break;
            }
            switch(type){
                case AnimType::LINEAR:
                    std::cout<<"Animation: duration-> "<<animEvent.duration<<"\ttype-> "<<showAnimType(type)<<"\n";
                    break;
                case AnimType::UNKNOWN:
                    std::cout<<"Animation: "<<showAnimType(type)<<"\n";
                    break;
                default:
                    std::cout<<"Animation: duration-> "<<animEvent.duration<<"\ttype-> "<<showAnimType(type)<<"\tf-> "<<animEvent.factor<<"\n";
                    break;
            }
        }
        void printEvent(Event& event){
            std::cout<<"Relative time: "<<event.timestamp<<"\n";
            Func eventFunc = event.animation.func;
            switch(eventFunc){
                case Func::FUNC3:
                    std::cout<<"FunctionAction: "<<showFunc(eventFunc)<<"\targs: "<<event.animation.f2arg1<<"\n";
                    break;
                default:
                    std::cout<<"FunctionAction: "<<showFunc(eventFunc)<<" <-Funcion invalida\n";
                    break;
            }
            std::cout<<"Duration: "<<event.animation.duration<<"\n";
        }
    public:
        LeverLoader()=default;
        const std::vector<ObsData>& getInfo() const{
            return obs;
        }
        const LevelData& getLevelInfo() const{
            return level;
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
        void printLevelInfo(){
            // Mostrar resultados
            //Cancion
            std::cout<<"--- Song ---\n";
            std::cout<<level.song<<"\n";
            //Secuencia de niveles
            std::cout<<"\n--- Level Sequence ---\n";
            if (level.phases.empty()) std::cout<<"(vacio)\n";
            for(auto& phase : level.phases){
                printPhase(phase);
            }
            std::cout<<"\n--- Phase Details ---\n";
            if (level.phaseData.empty()) std::cout<<"(vacio)\n";
            //Detalles de cada phase
            for(auto& phaseData : level.phaseData){
                std::cout<<"\n--- Phase Configuration ---\n";
                printPhaseConfig(phaseData);
                std::cout<<"\n--- Main Colors ---\n";
                for(auto& mainColor: phaseData.mainColors){
                    printColor(mainColor);
                }
                std::cout<<"\n--- Wall Colors ---\n";
                for(auto& wallColor: phaseData.wallColors){
                    printColor(wallColor);
                }
                std::cout<<"\n--- PollTime Rotation ---\n";
                printList(phaseData.pollTime);
                std::cout<<"\nPollTime DeltaRotX: ";
                printList(phaseData.pollDRot.pollRotX);
                std::cout<<"\nPollTime DeltaRotY: ";
                printList(phaseData.pollDRot.pollRotX);
                std::cout<<"\nPollTime DeltaRotZ: ";
                printList(phaseData.pollDRot.pollRotZ);
                std::cout<<"\n--- Poll Animations for BG ---\n";
                for(auto& animEvent : phaseData.BGAnimations){
                    printAnimEvent(animEvent);
                }
                std::cout<<"\n--- Poll Animations for Camnera ---\n";
                for(size_t i=0; i<phaseData.CamAnimations.size(); i++){
                    std::cout<<"Sequence #"<<i<<"\n";
                    for(size_t j=0; phaseData.CamAnimations[i].animations.size(); j++){
                        printAnimEvent(phaseData.CamAnimations[i].animations[j]);
                    }
                }
                std::cout<<"\n--- Events ---\n";
                for(size_t i=0; i<phaseData.events.size(); i++){
                    std::cout<<"Event #"<<i<<"\n";
                    printEvent(phaseData.events[i]);
                }
                //Falta
                std::cout << "\n--- Obstacles ---\n";
                for (size_t i = 0; i < phaseData.obs.size(); ++i) {
                    std::cout<<"Obstacle #"<<i<<"\n";
                    for (size_t j = 0; j < phaseData.obs[i].anims.size(); ++j) {
                        printAnimW(phaseData.obs[i].anims[j]);
                        for(auto& wall : phaseData.obs[i].anims[j].wall){
                            printCWall(wall);
                        }
                    }
                }
            }
            std::cout<<std::endl;
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