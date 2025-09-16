#ifndef DESKTOP_GLFW_PLATFORM_HPP
#define DESKTOP_GLFW_PLATFORM_HPP

#include <GLFW/glfw3.h>

#include "../include/Platform.hpp"

class DesktopGLFW: public IPlatform {
    private:
        /* data */
    public:
        DesktopGLFW();
        ~DesktopGLFW();
        bool configure();
};

DesktopGLFW::DesktopGLFW(){
    std::cout<<"Platform: Selecting Desktop (GLFW)"<<std::endl;
    //Initialize GLFW
    glfwInit();
}
DesktopGLFW::~DesktopGLFW(){
    std::cout<<"Platform: Closed Desktop (GLFW)"<<std::endl;
}
bool DesktopGLFW::configure(){
    //OpenGL
    
    return true;
}

#endif