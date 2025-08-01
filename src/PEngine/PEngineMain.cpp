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
    rManager.processShader()->setShaderMaker(gEngine.getShaderMaker());
    inited = true;
    return inited;
}