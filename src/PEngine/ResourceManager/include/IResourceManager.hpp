#ifndef RESOURCE_MANAGER_INTERFACE_HPP
#define RESOURCE_MANAGER_INTERFACE_HPP

#include "../GraphicsCore/include/GCore.hpp"

#include <memory>
#include <iostream>
#include <unordered_map>

class IShader;

class IStructuredFileManager {
    private:
    public:
        IStructuredFileManager() = default;
        virtual ~IStructuredFileManager(){}
        //Metodos para procesar archivos JSON, XML, etc, etc
};

class IShaderManager {
    protected:
        std::shared_ptr<IShaderMaker> shaderMaker = nullptr;
        std::unordered_map<std::string, std::unique_ptr<IShader>> shaderList;
    public:
        IShaderManager() = default;
        virtual ~IShaderManager(){}
        virtual IShader* loadShader(std::string name, const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) = 0;
        virtual IShader* getShader(std::string name) = 0;
        void setShaderMaker(std::shared_ptr<IShaderMaker> newShaderMaker){
            this->shaderMaker = std::move(newShaderMaker);
        }
};

class IResourceManager {
    private:
    protected:
        //std::unique_ptr<IShaderMaker> shaderMaker = nullptr;
        IStructuredFileManager* structuredFileManager;
        IShaderManager* shaderFileManager;
    public:
        IResourceManager(){};
        virtual ~IResourceManager(){};
        IStructuredFileManager* callStructManager() {
            return structuredFileManager;
        }
        IShaderManager* callShaderManager(){
            return shaderFileManager;
        }
};

#endif