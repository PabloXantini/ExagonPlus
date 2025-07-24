#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"

#include <iostream>

class WindowManager {
    private:
        bool GLADLinked = false;
        int monitorCount = 0;
        GLFWmonitor* mainMonitor;
        GLFWmonitor** allMonitors;
        bool linkGLAD();
        void checkMonitors();
    public:
        WindowManager(){};
        ~WindowManager(){};
        bool init(int GLmajorVersion, int GLminorVersion);
        Window* createWindow(unsigned int width, unsigned int height, const char* title, bool fullscreen = false, unsigned int monitorIndex = 1, Window* windowShared = nullptr);
};

#endif