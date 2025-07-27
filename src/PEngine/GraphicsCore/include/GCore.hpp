#ifndef G_CORE_HPP
#define G_CORE_HPP

#include "Scene.hpp"
#include "../Desktop/WindowManager.hpp"

#include <iostream>

class WindowManager;

class IBufferManager {
    public:
        IBufferManager() = default;
        virtual ~IBufferManager(){}
        virtual void decirAlgo() = 0;
};

class IRenderer {
    public:
        IRenderer() = default;
        virtual ~IRenderer(){}
        void render(Scene* scene){
            if(scene) scene->show();
        }
};

class IGCore {
    protected:
        IBufferManager* bufferManager;
        IRenderer* renderer; 
    public:
        IGCore(){};
        virtual ~IGCore(){};
        virtual WindowManager* getWinManager(){
            return nullptr;
        }
        IBufferManager* allocate(){
            return bufferManager;
        }
        IRenderer* render(){
            return renderer;
        }
};

#endif