#include "include/GraphicsCore.hpp"

GraphicCore::GraphicCore(){
    std::cout<<"El motor grafico debe haberse instanciado"<<std::endl;
}

GraphicCore::~GraphicCore(){
    delete gImplementation;
    std::cout<<"El motor grafico debe haberse limpiado"<<std::endl;
}

bool GraphicCore::init(){
    /*
        Desktop Initialization
    */
    //Inicia GLFW
    glfwInit();
    //Seleccion de Logica   
    gImplementation = new GCoreGL33(); 
    /*
        Mobile Initialization
    */
    return true;
}