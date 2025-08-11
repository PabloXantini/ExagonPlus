#include "WindowManager.hpp"
#include "Window.hpp"

Window::Window(SceneRenderer* renderContext, WindowResolution resolution, const char* title, GLFWmonitor* monitorSelected, Window* windowShared):
    renderer(renderContext),
    windowSharedReference(windowShared),
    monitorReference(monitorSelected)
{
    if(windowShared){
        windowReference = glfwCreateWindow(resolution.currentWidth, resolution.currentHeight, title, monitorSelected, windowShared->getWindowReference());
    }else{
        windowReference = glfwCreateWindow(resolution.currentWidth, resolution.currentHeight, title, monitorSelected, NULL);
    }
    if(windowReference == NULL){
        std::cout<<"ERROR: WINDOW COULD NOT CREATED"<<std::endl;
        glfwTerminate();
    }
    this->resolution = resolution;
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
