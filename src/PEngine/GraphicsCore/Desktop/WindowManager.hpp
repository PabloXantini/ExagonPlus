#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/GCore.hpp"
#include "Time.hpp"
#include "Window.hpp"

#include <iostream>
#include <vector>

class WindowManager {
    private:
        bool GLADLinked = false;
        SceneRenderer* renderer;
        std::vector<Window*> windows = {};
        int monitorCount = 0;
        GLFWmonitor* mainMonitor;
        GLFWmonitor** allMonitors;
        bool linkGLAD();
        void checkMonitors();
    protected:
        Time* time;
        virtual void setGLconfig(Window* window) = 0;
        virtual void renderInWindow() = 0;
    public:
        WindowManager(Time* time);
        ~WindowManager();
        bool init(int GLmajorVersion, int GLminorVersion);
        Window* createWindow(unsigned int width, unsigned int height, const char* title, bool fullscreen = false, unsigned int monitorIndex = 1, Window* windowShared = nullptr);
        void runAsOnlyWindow(Window* mainWindow);
        void runAsVariousWindows(Window* mainWindow);
};

//Callbacks
void doAtCloseWindow(GLFWwindow* window);

#endif