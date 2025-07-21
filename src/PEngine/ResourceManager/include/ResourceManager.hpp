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
        IStructuredFileLoader* processsStructuredFile(){
            return rmImplementation->processStruct();
        }
};

#endif