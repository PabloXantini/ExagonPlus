#include "WindowManager.hpp"
#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, const char* title, GLFWmonitor* monitorSelected, Window* windowShared):
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
    this->width = width;
    this->height = height;
    glfwMakeContextCurrent(windowReference);
    glfwSetWindowUserPointer(windowReference, this);
    //Callbacks settings
    glfwSetWindowCloseCallback(windowReference, doAtCloseWindow);
}
Window::~Window(){
    std::cout<<"Se destruyo esta ventana"<<std::endl;
    glfwDestroyWindow(windowReference);
}
