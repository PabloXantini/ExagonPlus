#include "include/ResourceManager.hpp"

ResourceManager::ResourceManager(){
    std::cout<<"El administrador de recursos debe haberse instanciado"<<std::endl;
}

ResourceManager::~ResourceManager(){
    delete rmImplementation;
    std::cout<<"El administrador de recursos debe haberse limpiado"<<std::endl;
}

bool ResourceManager::init(){
    //Seleccionar la logica de acuerdo con la plataforma
    /*
        Desktop initialization
    */
    rmImplementation = new ResourceManagerDesk();
    return true;
}