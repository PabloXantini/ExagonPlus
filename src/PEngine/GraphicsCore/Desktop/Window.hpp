#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "WindowManager.hpp"

#include <iostream>

class SceneRenderer;
class Scene;

struct WindowResolution{
    unsigned int width;
    unsigned int height;
    unsigned int currentWidth;
    unsigned int currentHeight;
};

class Window {
    private:
        //Scene Specs
        SceneRenderer* renderer;
        Scene* scene = nullptr;
        //Window Attributes
        GLFWmonitor* monitorReference;
        GLFWwindow* windowReference;
        Window* windowSharedReference;
        WindowResolution resolution;
        const char* title;
        bool shouldClose = false;
        //bool fullscreenEnabled;
    public:
        Window(SceneRenderer* renderContext, WindowResolution resolution, const char* title, GLFWmonitor* monitorSelected, Window* windowShared);
        ~Window();
        GLFWwindow* getWindowReference(){
            return this->windowReference;
        }
        unsigned int getWidth(){
            return this->resolution.currentWidth;
        }
        unsigned int getHeight(){
            return this->resolution.currentHeight;
        }
        bool isShouldClose(){
            return this->shouldClose;
        }
        void markAsClosed(bool value){
            this->shouldClose = value;
        }
        void setScene(Scene* scene){
            this->scene = scene;
        }
        void close();
        void render(Time* time);
};

#endif