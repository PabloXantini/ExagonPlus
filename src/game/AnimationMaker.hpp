#ifndef ANIMATION_MAKER_HPP
#define ANIMATION_MAKER_HPP

#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>

enum class AnimType {
    BGLINEAR,
    BGEASEIN,
    BGEASEOUT,
    BGEASEINOUT,
    LINEAR,
    EASEIN,
    EASEOUT,
    EASEINOUT,
    UNKNOWN
};

class Animation {
    private:
        //Variables propias de la clase
        bool activated=false;
        float timeElapsed;
        float duration;
        //Flags
        bool hasInited=false;
        bool hasFinished=false;
        bool executing=false;
        AnimType type;
        std::function<void(Animation*, float, unsigned int)> callback;           //Cambio de BG
        std::function<void(Animation*, float)> callback2;               //General
        //Menos relevantes
        unsigned int newsides;
        float toscale;
        float easing;
        //Funciones de movimiento
        float linear(float t){
            return t;
        }
        float ease_in(float t, float ease){
            if(ease>1) return (float)(pow(t,ease));
            return 0.0f;
        }
        float ease_out(float t, float ease){
            if(ease>1) return (float)(1.0f-pow(1.0f-t,ease));
            return 0.0f;
        }
        float ease_in_out(float t, float ease){
            if(ease>1) return (float)(pow(t,ease)/(pow(t,ease)+pow(1.0f-t,ease)));
            return 0.0f;
        }
    public:     
        Animation(unsigned int sides, float duration, std::function<void(Animation*, float, unsigned int)> cb, AnimType type){
            callback=cb;
            newsides=sides;
            this->duration=duration;
            this->type=type;
            init();
        };
        Animation(float duration, std::function<void(Animation*, float)> cb, AnimType type){
            callback2=cb;
            this->duration=duration;
            this->type=type;
            init();
        };
        Animation(unsigned int sides, float duration, float easing, std::function<void(Animation*, float, unsigned int)> cb, AnimType type){
            callback=cb;
            newsides=sides;
            this->duration=duration;
            this->easing=easing;
            this->type=type;
            init();
        };
        Animation(float duration, float easing, std::function<void(Animation*, float)> cb, AnimType type){
            callback2=cb;
            this->duration=duration;
            this->easing=easing;
            this->type=type;
            init();
        };
        ~Animation(){
            //std::cout<<"Murio la animacion"<<std::endl;
        }
        void execute(float deltatime){
            if(!activated) return;
            if(executing==false) {
                hasInited=true;
                //std::cout<<"Inicio la accion"<<std::endl;
            }else{
                hasInited=false;
            }
            executing=true;
            timeElapsed+=deltatime;
            //Normalizar
            float progress=std::min(timeElapsed/duration, 1.0f);
            //Aplicar la funcion
            float delta=0.0f;
            switch(type){
                case AnimType::BGLINEAR:
                    delta=linear(progress);
                    callback(this, delta, newsides);
                    break;
                case AnimType::BGEASEIN:
                    delta=ease_in(progress, easing);
                    callback(this, delta, newsides);
                    break;
                case AnimType::BGEASEOUT:
                    delta=ease_out(progress, easing);
                    callback(this, delta, newsides);
                    break;
                case AnimType::BGEASEINOUT:
                    delta=ease_in_out(progress, easing);
                    callback(this, delta, newsides);
                    break;
                case AnimType::LINEAR:
                    delta=linear(progress);
                    callback2(this, delta);
                    break;
                case AnimType::EASEIN:
                    delta=ease_in(progress, easing);
                    callback2(this, delta);
                    break;
                case AnimType::EASEOUT:
                    delta=ease_out(progress, easing);
                    callback2(this, delta);
                    break;
                case AnimType::EASEINOUT:
                    delta=ease_in_out(progress, easing);
                    callback2(this, delta);
                    break;
            }
            //Condicion de fin
            if(progress>=1.0f){
                //std::cout<<"Termino la accion"<<std::endl;
                activated=false;
                hasFinished=true;
                executing=false;
                timeElapsed=0.0f;
            }
        }
        void init(){
            //std::cout<<"Disponible"<<std::endl;
            timeElapsed=0.0f;
            activated=true;
            hasInited=false;
            hasFinished=false;
            executing=false;
        }
        bool Inited(){
            return hasInited;
        }
        bool Finished(){
            return hasFinished;
        }
};

#endif