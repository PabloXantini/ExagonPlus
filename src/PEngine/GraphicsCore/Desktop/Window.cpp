#include "WindowManager.hpp"
#include "Window.hpp"

Window::Window(SceneRenderer* renderContext, WindowResolution resolution, const char* title, GLFWmonitor* monitorSelected, bool fullscreen, Window* windowShared):
    renderer(renderContext),
    windowSharedReference(windowShared),
    monitorReference(monitorSelected)
{
    if(fullscreen && monitorSelected){
        const GLFWvidmode* mode = glfwGetVideoMode(monitorSelected);
        resolution.currentWidth = mode->width;
        resolution.currentHeight = mode->height;
    }
    if(windowShared){
        windowReference = glfwCreateWindow(resolution.currentWidth, resolution.currentHeight, title, monitorSelected, windowShared->getWindowReference());
    }else{
        windowReference = glfwCreateWindow(resolution.currentWidth, resolution.currentHeight, title, monitorSelected, NULL);
    }
    if(windowReference == NULL){
        std::cout<<"ERROR: WINDOW COULD NOT CREATED"<<std::endl;
        glfwTerminate();
    }
    if(!fullscreen && monitorSelected){
        int posX, posY;
        glfwGetMonitorPos(monitorSelected, &posX, &posY);
        glfwSetWindowPos(windowReference, posX, posY);
    }
    glfwGetWindowPos(windowReference, &position_x, &position_y);
    this->resolution = resolution;
    this->fullScreen = fullscreen;
    this->title = title;
    glfwMakeContextCurrent(windowReference);
    //User Pointer
    glfwSetWindowUserPointer(windowReference, this);
    //Callbacks settings
    glfwSetWindowCloseCallback(windowReference, doAtCloseWindow);
}
Window::~Window(){
    std::cout<<"Se destruyo esta ventana"<<std::endl;
    std::cout<<this->getWidth()<<std::endl;
    glfwDestroyWindow(windowReference);
}
void Window::close(){
    markAsClosed(true);
    glfwSetWindowShouldClose(windowReference, GL_FALSE);
}
void Window::render(Time* time){
    while(time->isFrameDelayed()){
        if (scene) scene->update(time->getDeltaTime());
        //std::cout<<"Si ves esto mas veces es que se retraso el frame\n";
    }
    renderer->render(scene);
    glfwSwapBuffers(windowReference);
}
