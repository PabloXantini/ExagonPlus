#ifndef G_CORE_GL33_HPP
#define G_CORE_GL33_HPP

#include "../GCoreDesktop.hpp"
#include "../Time.hpp"

#include "WRendererGL33.hpp"
#include "../../GL/GL33/ShaderMaker33.hpp"
#include "../../GL/GL33/BufferManager33.hpp"
#include "../../GL/GL33/RendererMaker33.hpp"

class GCoreGL33: public GCoreDesktop {
    private:
    public:
        GCoreGL33(){
            std::cout<<"Este codigo del motor grafico debe haberse inicializado"<<std::endl;
            //Final instance creation
            //Global Desktop Instance
            time = new Time();
            windowManager = new WindowRendererGL33(time);
            //Especific Implementation
            shaderMaker = std::make_shared<ShaderMakerGL33>();
            bufferManager = new BufferManagerGL33();
            meshCreator = new MeshCreator(bufferManager);
            renderCreator = new RendererMaker33();
            windowManager->init(3, 3);
        }
        ~GCoreGL33(){
            delete meshCreator;
            delete bufferManager;
            std::cout<<"Este codigo del motor grafico debe haberse limpiado"<<std::endl;
        }
        
};

#endif