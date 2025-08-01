#ifndef RESOURCE_MANAGER_PLATFORM_HPP
#define RESOURCE_MANAGER_PLATFORM_HPP

#include "IResourceManager.hpp"
#include "../RMDesktop/ResourceManager.hpp"

#include <iostream>

class ResourceManager {
    private:
        IResourceManager* rmImplementation;
    public:
        ResourceManager();
        ~ResourceManager();
        bool init();
        IStructuredFileManager* processsStructuredFile(){
            return rmImplementation->callStructManager();
        }
        IShaderManager* processShader(){
            return rmImplementation->callShaderManager();
        }
};

#endif