#ifndef RESOURCE_MANAGER_INTERFACE_HPP
#define RESOURCE_MANAGER_INTERFACE_HPP

#include <iostream>

class IStructuredFileLoader {
    private:
    public:
        IStructuredFileLoader() = default;
        virtual ~IStructuredFileLoader(){}
        //Metodos para procesar archivos JSON, XML, etc, etc
};

class IShaderFileLoader {
    private:
    public:
        IShaderFileLoader() = default;
        virtual ~IShaderFileLoader(){}
        //Metodos para procesar archivos Shader (Aunque es solo uno xd)
};

class IResourceManager {
    private:
    protected:
        IStructuredFileLoader* structuredFileLoader;
        IShaderFileLoader* shaderFileLoader;
    public:
        IResourceManager():
            structuredFileLoader(structuredFileLoader),
            shaderFileLoader(shaderFileLoader)
        {};
        virtual ~IResourceManager(){};
        IStructuredFileLoader* processStruct() {
            return structuredFileLoader;
        };
};

#endif