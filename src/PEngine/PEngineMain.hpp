#ifndef PENGINE_HPP
#define PENGINE_HPP

//Cores
#include "GraphicsCore/include/GraphicsCore.hpp"
//ResourceManager
#include "ResourceManager/include/ResourceManager.hpp"

#include <iostream>
#include <stdexcept>

class PEngine {
    private:
        //Variables
        bool inited = false;
        //Components
        ResourceManager rManager;
        GraphicCore gEngine;
        //AudioCore aEngine;
    public:
        PEngine();
        bool init();
        bool close();
        GraphicCore& getGraphics(){ 
            if (!inited) throw std::runtime_error("ERROR: GAME ENGINE NOT INITIALIZED"); 
            return gEngine;
        }
};

#endif