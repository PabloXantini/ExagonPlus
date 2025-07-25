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
    public:
        Window(unsigned int width, unsigned int height, const char* title, GLFWmonitor* monitorSelected, Window* windowShared);
        ~Window();
        GLFWwindow* getWindowReference(){
            return windowReference;
        }
        unsigned int getWidth(){
            return width;
        }
        unsigned int getHeight(){
            return height;
        }
};

#endif