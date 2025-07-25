#ifndef G_CORE_GL33_HPP
#define G_CORE_GL33_HPP

#include "../GCoreDesktop.hpp"

#include "WRendererGL33.hpp"
#include "BufferManager.hpp"

class GCoreGL33: public GCoreDesktop {
    private:
    public:
        GCoreGL33(){
            std::cout<<"Este codigo del motor grafico debe haberse inicializado"<<std::endl;
            windowManager = new WindowRenderer();
            bufferManager = new BufferManager();
            
            windowManager->init(3, 3);
        }
        ~GCoreGL33(){
            delete bufferManager;
            std::cout<<"Este codigo del motor grafico debe haberse limpiado"<<std::endl;
        }
        
};

#endif