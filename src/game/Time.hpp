#ifndef TIME_HPP
#define TIME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
//El tiempo general
class Timer {
    private:
        float temp;
        float time;
        float deltaTime;
    public:
        Timer() {
            glfwSetTime(0.0f);
            temp=glfwGetTime();
            std::cout<<"Oh me creooo, dice el tiempo"<<std::endl;
        };
        //Getters
        float getTime() {
            time=glfwGetTime();
            return time;
        }
        float getDeltaTime() {
            time=glfwGetTime();
            deltaTime=std::min(time-temp,0.5f);
            temp=time;
            return deltaTime;
        }
        //Setters
        void restart(float& t) {
            t=0.0f;
            time=0.0f;
            glfwSetTime(0.0f);
            temp=glfwGetTime();
        }  
};
//Me sirve para cosas que se repiten en sierto intervalo
class Chronometer {
    private:
        float timer = 0.0f;         //Valor anterior en el tiempo
        float tracktime = 1.0f;     //Valor aspirado
    public:
        Chronometer(float tracktime) {
            this->tracktime = tracktime;
        }
        //Setters
        void setTTime(float totime){
            tracktime = totime;
        }
        //Me va servir para checar
        bool track(float time){
            if((time-timer)>=tracktime){
                timer = time;
                return true;
            }
            return false;
        }
        //Reinicia el cronometro
        void restart(){
            timer = 0.0f;
        }
};
//Me sirve para cosas demasiado precisas
class cbChronometer {
    private:
        float timer = 0.0f;         //Valor anterior del tiempo
        float elapsedTime = 0.0f;   //Valor local del tiempo
        float tracktime = 1.0f;     //Valor aspirado
    public:
        cbChronometer(float tracktime) {
            this->tracktime = tracktime;
        }
        //Setters
        void setTTime(float totime){
            tracktime=totime;
        }
        //Me va servir para checar por deltatime
        bool trackDelta(float deltaTime){
            elapsedTime+=deltaTime;
            if(elapsedTime>=tracktime){
                //Si el tiempo se pasa demasiado, me quedo con la rebaba y asi el cronometro termina antes
                elapsedTime=-tracktime;
                return true;
            }
            return false;
        }
        //Me va servir para checar por tiempo global
        bool track(float time){
            float diff=time-timer;
            float leftover=diff-tracktime;
            if(diff>=tracktime){
                //Si el tiempo se pasa demasiado, ajusto el timer para que intente comparar correctamente
                timer=time-leftover;
                return true;
            }
            return false;
        }
        //Reincia
        void restart(){
            timer = 0.0f;
            elapsedTime = 0.0f;
        }
};
#endif