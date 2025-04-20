#ifndef TIME_HPP
#define TIME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>

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
        void restart() {
            time=0.0f;
            glfwSetTime(0.0f);
        }  
};

#endif