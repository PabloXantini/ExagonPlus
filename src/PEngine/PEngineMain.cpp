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

GameObject3D* PEngine::createGameObject3D(Renderer* renderer){
    return new GameObject3D(this, renderer);
}

GameObject2D* PEngine::createGameObject2D(Renderer* renderer){
    return new GameObject2D(this, renderer);
}