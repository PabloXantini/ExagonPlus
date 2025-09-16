#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/GCore.hpp"
//Must abstract
#include "../GL/ContextManager.hpp"
#include "Time.hpp"
#include "Window.hpp"

#include <iostream>
#include <vector>

class WindowManager {
    private:
        bool GLADLinked = false;

        ContextManager* ctxManager;
        SceneRenderer* renderer;
        std::vector<Window*> windows = {};
        int monitorCount = 0;
        GLFWmonitor* mainMonitor;
        GLFWmonitor** allMonitors;
        bool linkGLAD();
        void checkMonitors();
    protected:
        Time* time;
        //Setters
        void setContextManager(ContextManager* CtxManager);
        virtual void setGLconfig(Window* window){};
        virtual void renderInWindow(){};
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