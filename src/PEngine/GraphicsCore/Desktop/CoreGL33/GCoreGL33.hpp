#ifndef G_CORE_GL33_HPP
#define G_CORE_GL33_HPP

#include "../GCoreDesktop.hpp"
#include "../Time.hpp"

#include "WRendererGL33.hpp"
#include "../../GL/GL33/ShaderMaker33.hpp"
#include "../../GL/GL33/BufferManager33.hpp"

class GCoreGL33: public GCoreDesktop {
    private:
    public:
        GCoreGL33(){
            std::cout<<"Este codigo del motor grafico debe haberse inicializado"<<std::endl;
            //Final instance creation
            time = new Time();
            windowManager = new WindowRendererGL33(time);
            shaderMaker = std::make_shared<ShaderMakerGL33>();
            bufferManager = new BufferManagerGL33();
            windowManager->init(3, 3);
        }
        ~GCoreGL33(){
            delete bufferManager;
            std::cout<<"Este codigo del motor grafico debe haberse limpiado"<<std::endl;
        }
        
};

#endif