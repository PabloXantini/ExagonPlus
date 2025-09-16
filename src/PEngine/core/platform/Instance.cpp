#include "include/Instance.hpp"

Platform::Platform(){
    std::cout<<"Platform instancing..."<<std::endl;
}
Platform::~Platform(){
    delete pImpl;
    std::cout<<"Platform closed"<<std::endl;
}
bool Platform::init(){
    /*
        You must use macros for specify PLATFORM
    */
    //Any Desktop Compatible with GLFW
    pImpl = new DesktopGLFW();
    //Mobile
    return true;
}
bool Platform::setup(){
    bool res = pImpl->configure();
    return res;
}