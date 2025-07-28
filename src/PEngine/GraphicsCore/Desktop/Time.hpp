#ifndef TIME_HPP
#define TIME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Time {
    private:
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
        void check(){
            this->currentTimeCheck = glfwGetTime();
            this->deltaTime = currentTimeCheck - lastTimeCheck;
            this->lastTimeCheck+=deltaTime;
        }
};

#endif