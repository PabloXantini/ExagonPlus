#ifndef GRAPHICS_CORE_PLATFORM_HPP
#define GRAPHICS_CORE_PLATFORM_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Platform Especification
#include "GCore.hpp"
#include "../Desktop/CoreGL33/GCoreGL33.hpp"

#include <iostream>

class GraphicCore {
    private:
        IGCore* gImplementation;
    public:
        GraphicCore();
        ~GraphicCore();
        bool init();
        WindowManager* getWinManager(){
            return gImplementation->getWinManager();
        }
        IBufferManager* allocate(){
            return gImplementation->allocate();
        }
        std::shared_ptr<IShaderMaker> getShaderMaker(){
            return gImplementation->getShaderMaker();
        }
};

#endif