#ifndef GRAPHICS_CORE_PLATFORM_HPP
#define GRAPHICS_CORE_PLATFORM_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Desktop Especification
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
};

#endif