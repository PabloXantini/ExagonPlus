#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

class ContextManager;
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
        //Context administration
        ContextManager* ctxManager;
        //Scene Specs
        SceneRenderer* renderer;
        Scene* scene = nullptr;
        //Window Attributes
        unsigned int sharedID;
        unsigned int contextID;
        GLFWmonitor* monitorReference;
        GLFWwindow* windowReference;
        Window* windowSharedReference;
        //Window Common Data
        WindowResolution resolution;
        int position_x;
        int position_y;
        const char* title;
        bool fullScreen = false;
        bool shouldClose = false;
        //bool fullscreenEnabled;
    public:
        Window(ContextManager* contextMgr, SceneRenderer* renderContext, WindowResolution resolution, const char* title, GLFWmonitor* monitorSelected, bool fullscreen, Window* windowShared);
        ~Window();
        GLFWwindow* getWindowReference(){
            return this->windowReference;
        }
        unsigned int getContextID(){
            return this->contextID;
        }
        unsigned int getSharedID(){
            return this->sharedID;
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
        void makeCurrent();
        void close();
        void render(Time* time);
};

#endif