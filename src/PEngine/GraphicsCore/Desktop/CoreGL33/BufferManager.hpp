#ifndef BUFFER_MANAGER_HPP
#define BUFFER_MANAGER_HPP

#include "../../include/GCore.hpp"

//#include <iostream>

class BufferManager : public IBufferManager {
    public:
        BufferManager(){
            std::cout<<"Hola, esto significa que el BufferManager se instancio correctamente"<<std::endl;
        }
        void decirAlgo() override {
            std::cout<<"Bienvenido a la programacion, hijo de perr4"<<std::endl;
        }
};

#endif