#ifndef G_CORE_GL33_HPP
#define G_CORE_GL33_HPP

//Not include
#include "../GCoreDesktop.hpp"
#include "../Time.hpp"

//Not include
#include "WRendererGL33.hpp"
#include "../../GL/ContextManager.hpp"

#include "../Transform.hpp"
#include "ShaderMaker33.hpp"
#include "BufferManager33.hpp"
#include "RendererMaker33.hpp"

class GCoreGL33: public GCoreDesktop {
    private:
    public:
        GCoreGL33(){
            std::cout<<"Este codigo del motor grafico debe haberse inicializado"<<std::endl;
            //Final instance creation
            //Global Desktop Instance
            time = new Time();
            contextManager = new ContextManager();
            windowManager = new WindowRendererGL33(contextManager, time);
            //Especific Implementation
            shaderMaker = std::make_shared<ShaderMakerGL33>();
            bufferManager = new BufferManagerGL33();
            modelCreator = new ModelCreator();
            meshCreator = new MeshCreator(bufferManager);
            transformUser = new TransformUserGL();
            renderCreator = new RendererMaker33();
            //Initialization
            windowManager->init(3, 3);
            bufferManager->setContextManager(contextManager);
        }
        ~GCoreGL33(){
            delete modelCreator;
            delete meshCreator;
            delete transformUser;
            delete bufferManager;
            std::cout<<"Este codigo del motor grafico debe haberse limpiado"<<std::endl;
        }
        
};

#endif