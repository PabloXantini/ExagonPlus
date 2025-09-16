#ifndef GRAPHICS_INSTANCE_HPP
#define GRAPHICS_INSTANCE_HPP

#include "Graphics.hpp"
//API Especification
#include "../GL/GL33/gl33.hpp"

class Graphics{
    private:
        //Implementation
        IGraphics* gImpl;
    public:
        Graphics();
        ~Graphics();
        //Instantation
        bool init();
        //Main Functions
};

#endif