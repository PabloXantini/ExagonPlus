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
    EASEINOUT
};

class Animation {
    private:
        bool activated=false;
        float timeElapsed;
        float duration;
        AnimType type;
        std::function<void(float, int)> callback;           //Cambio de BG
        std::function<void(float, float)> callback2;        //Cambio de Escala
        std::function<void(float, int, float)> callback3;   //Cambio de bg non linear
        std::function<void(float, float, float)> callback4; //Cambio de escala non linear
        //Menos relevantes
        unsigned int newsides;
        float toscale;
        float easing;
    public:     
        Animation(unsigned int sides, float duration, std::function<void(float, int)> cb, AnimType type){
            callback=cb;
            newsides=sides;
            this->duration=duration;
            this->type=type;
            init();
        };
        Animation(unsigned int sides, float duration, float easing, std::function<void(float, int)> cb, AnimType type){
            callback=cb;
            newsides=sides;
            this->duration=duration;
            this->easing=easing;
            this->type=type;
            init();
        };
        void execute(float deltatime){
            if(!activated) return;
            timeElapsed+=deltatime;
            //Normalizar
            float progress=std::min(timeElapsed/duration, 1.0f);
            //Aplicar la funcion
            float delta=0.0f;
            switch(type){
                case AnimType::BGLINEAR:
                    delta=linear(progress);
                    callback(delta, newsides);
                    break;
                case AnimType::BGEASEIN:
                    delta=ease_in(progress, easing);
                    callback(delta, newsides);
                    break;
                case AnimType::BGEASEOUT:
                    delta=ease_out(progress, easing);
                    callback(delta, newsides);
                    break;
                case AnimType::BGEASEINOUT:
                    delta=ease_in_out(progress, easing);
                    callback(delta, newsides);
                    break;
            }
            //Condicion de fin
            if(progress>=1.0f){
                std::cout<<"Termino la accion"<<std::endl;
                activated=false;
                timeElapsed=0.0f;
            }
        }
        void init(){
            std::cout<<"Inicio accion"<<std::endl;
            timeElapsed=0.0f;
            activated=true;
        }
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
};

#endif