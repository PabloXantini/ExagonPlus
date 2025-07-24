#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "WindowManager.hpp"

#include <iostream>

class Window {
    private:
        GLFWmonitor* monitorReference;
        GLFWwindow* windowReference;
        Window* windowSharedReference;
        unsigned int width;
        unsigned int height;
        const char* title;
        bool fullscreenEnabled;
        //unsigned int windowSharedID;
        GLFWwindow* getWindowReference(){
            return windowReference;
        }
    public:
        Window(int width, unsigned int height, const char* title, GLFWmonitor* monitorSelected, Window* windowShared):
            windowSharedReference(windowShared),
            monitorReference(monitorSelected)
        {
            if(windowShared){
                windowReference = glfwCreateWindow(width, height, title, monitorSelected, windowShared->getWindowReference());
            }else{
                windowReference = glfwCreateWindow(width, height, title, monitorSelected, NULL);
            }
            if(windowReference == NULL){
                std::cout<<"ERROR: WINDOW COULD NOT CREATED"<<std::endl;
                glfwTerminate();
            }
            glfwMakeContextCurrent(windowReference);
        }
        ~Window(){}
};

#endif