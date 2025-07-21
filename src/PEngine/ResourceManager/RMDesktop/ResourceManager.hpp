#ifndef RESOURCE_MANAGER_DESK_HPP
#define RESOURCE_MANAGER_DESK_HPP

#include "../include/IResourceManager.hpp"


class ResourceManagerDesk : public IResourceManager {
    private:
    public:
        ResourceManagerDesk(){
            std::cout<<"Este codigo del RM debe haberse inicializado"<<std::endl;  
        }
        ~ResourceManagerDesk(){
            //delete structuredFileLoader;
            std::cout<<"Este codigo del RM debe haberse limpiado"<<std::endl;
        }
};

#endif