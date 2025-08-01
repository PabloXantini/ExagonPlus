#ifndef G_CORE_HPP
#define G_CORE_HPP

#include "../../Utils/Scene.hpp"
#include "../Desktop/WindowManager.hpp"
#include "Shader.hpp"

#include <memory>
#include <iostream>

class WindowManager;

//Abstract Factory of Shaders
class IShaderMaker{
    public:
        IShaderMaker() = default;
        virtual ~IShaderMaker() = default;
        virtual std::unique_ptr<IShader> createShader() = 0;
};

class IBufferManager {
    public:
        IBufferManager() = default;
        virtual ~IBufferManager(){}
        virtual void createBuffer3D() = 0;
        virtual void createBuffer2D() = 0;
};

class IRenderer {
    public:
        IRenderer() = default;
        virtual ~IRenderer(){}
        void render(Scene* scene){
            if(!scene) return;
            scene->show();
        }
};

class IGCore {
    protected:
        std::shared_ptr<IShaderMaker> shaderMaker = nullptr;
        IBufferManager* bufferManager;
        IRenderer* renderer; 
    public:
        IGCore(){};
        virtual ~IGCore(){};
        virtual WindowManager* getWinManager(){
            return nullptr;
        }
        virtual Time* manageTime(){
            return nullptr;
        }
        IBufferManager* allocate(){
            return bufferManager;
        }
        IRenderer* render(){
            return renderer;
        }
        std::shared_ptr<IShaderMaker> getShaderMaker(){
            return std::move(shaderMaker);
        }
};

#endif