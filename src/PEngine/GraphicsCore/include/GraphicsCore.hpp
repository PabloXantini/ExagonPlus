#ifndef GRAPHICS_CORE_PLATFORM_HPP
#define GRAPHICS_CORE_PLATFORM_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GCore.hpp"
#include "../CoreGL33/GCoreGL33.hpp"

#include <iostream>

class GraphicCore {
    private:
        IGCore* gImplementation;
    public:
        GraphicCore();
        ~GraphicCore();
        bool init();
        IBufferManager* allocate(){
            return gImplementation->allocate();
        }
};

#endif