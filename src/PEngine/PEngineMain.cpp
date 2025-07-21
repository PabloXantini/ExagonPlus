#include "PEngineMain.hpp"

PEngine::PEngine():
    rManager(), 
    gEngine() 
{
    std::cout<<"El motor debe haberse instanciado"<<std::endl;
}

bool PEngine::init(){
    if(!rManager.init()) return false;
    if(!gEngine.init()) return false;
    inited = true;
    return inited;
}