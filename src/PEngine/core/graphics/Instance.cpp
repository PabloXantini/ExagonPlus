#include "include/Instance.hpp"

Graphics::Graphics(){
    std::cout<<"Graphics instancing..."<<std::endl;
}
Graphics::~Graphics(){
    delete gImpl;
    std::cout<<"Graphics closed"<<std::endl;
}
bool Graphics::init(){
    /*
        You must use macros for specify API by PLATFORM
    */
    //Desktop and OpenGL33
    gImpl = new GL33();
    return true;
}