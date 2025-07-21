#ifndef G_CORE_GL33_HPP
#define G_CORE_GL33_HPP

#include "../include/GCore.hpp"

#include "BufferManager.hpp"

class GCoreGL33: public IGCore {
    private:
    public:
        GCoreGL33(){
            std::cout<<"Este codigo del motor grafico debe haberse inicializado"<<std::endl;
            bufferManager = new BufferManager();
        }
        ~GCoreGL33(){
            delete bufferManager;
            std::cout<<"Este codigo del motor grafico debe haberse limpiado"<<std::endl;
        }
};

#endif