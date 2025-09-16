#ifndef PENGINE_HPP
#define PENGINE_HPP

//Cores
#include "PlatformCore/include/PlatformCore.hpp"
#include "GraphicsCore/include/GraphicsCore.hpp"
//ResourceManager
#include "ResourceManager/include/ResourceManager.hpp"
//Objects
#include "UComponents/GameObject.hpp"

#include <iostream>
#include <stdexcept>

class PEngine {
    private:
        //Variables
        bool inited = false;
        //Components
        ResourceManager rManager;
        PlatformCore platform;
        GraphicCore gEngine;
        //AudioCore aEngine;
    public:
        PEngine();
        bool init();
        bool close();
        ResourceManager& getResourceManager(){
            if (!inited) throw std::runtime_error("ERROR: GAME ENGINE NOT INITIALIZED");
            return rManager;
        }
        PlatformCore& getPlatform(){
            if(!inited) throw std::runtime_error("ERROR: GAME ENGINE NOT INITIALIZED");
            return platform;
        }
        GraphicCore& getGraphics(){ 
            if (!inited) throw std::runtime_error("ERROR: GAME ENGINE NOT INITIALIZED"); 
            return gEngine;
        }
        GameObject3D* createGameObject3D(Renderer* renderer = nullptr);
        GameObject2D* createGameObject2D(Renderer* renderer = nullptr);
};

#endif