#ifndef TIME_HPP
#define TIME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Time {
    private:
        const float timeSlice = 1.0f/60.0f;
        float timeBetweenFrames = 0.0f;
        float deltaTime = 0.0f;
        float currentTimeCheck = 0.0f;
        float lastTimeCheck = 0.0f;
    public:
        Time(){
            glfwSetTime(0.0f);
        };
        ~Time() = default;
        float getTime(){
            return this->currentTimeCheck;
        }
        float getDeltaTime(){
            return this->deltaTime;
        }
        bool isFrameDelayed(){
            if(timeBetweenFrames > timeSlice){
                deltaTime = timeSlice;
                timeBetweenFrames -= timeSlice;
                return true;
            }else{
                return false;
            }
        }
        void check(){
            this->currentTimeCheck = glfwGetTime();
            this->deltaTime = currentTimeCheck - lastTimeCheck;
            if(this->deltaTime > 1.0f) deltaTime = 1.0f;
            this->lastTimeCheck+=deltaTime;
            this->timeBetweenFrames+=deltaTime;
        }
        void sync(){
            this->currentTimeCheck = glfwGetTime();
            this->lastTimeCheck = currentTimeCheck;
        }
};

#endif