#ifndef TIME_HPP
#define TIME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Timer {
    private:
        float temp;
        float time;
        float deltaTime;
    public:
        Timer() {
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
            deltaTime=time-temp;
            temp=time;
            return deltaTime;
        }  
};

#endif