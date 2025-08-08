#ifndef G_CORE_HPP
#define G_CORE_HPP

#include "../../Utils/Scene.hpp"
#include "../../Utils/Vertex.h"
#include "../Desktop/WindowManager.hpp"
#include "Shader.hpp"
#include "Buffer.hpp"
#include "Mesh.hpp"
#include "Transformation3D.hpp"

#include <memory>
#include <vector>
#include <iostream>

class Time;
class WindowManager;

class SceneRenderer {
    public:
        SceneRenderer(){}
        ~SceneRenderer(){}
        void render(Scene* scene){
            if(!scene) return;
            scene->show();
        }
};
//Abstract Factory of Shaders
class IShaderMaker{
    public:
        IShaderMaker() = default;
        virtual ~IShaderMaker() = default;
        virtual std::unique_ptr<IShader> createShader() = 0;
};

//Factory of Meshes
class MeshCreator {
    protected:
        IBufferManager* bufferManagerUsed;
    public:
        MeshCreator(IBufferManager* bufferManager): bufferManagerUsed(bufferManager){};
        ~MeshCreator(){}
        Mesh<WVertex3D>* createMesh(std::vector<WVertex3D>& verts, std::vector<unsigned int>* indexes = nullptr){
            return new Mesh<WVertex3D>(bufferManagerUsed, verts, indexes, nullptr);
        };
};

//Abstract Factory of Transforms
class TransformUser {
    public:
        TransformUser() = default;
        virtual ~TransformUser() = default;
        virtual Transform3D* useTransform3D() = 0;
        //Transform2D* useTransform2D() = 0;
};

class Renderer {
    protected:
        IShader* shader;
    public:
        Renderer(IShader* shader): shader(shader){};
        virtual ~Renderer(){}
        virtual void draw(IMesh* mesh) = 0;
};
//Factory of Renderers
class IRendererMaker {
    public:
        IRendererMaker(){};
        virtual ~IRendererMaker(){};
        virtual Renderer* makeRenderer(IShader* shader) = 0;
};

class IGCore {
    protected:
        std::shared_ptr<IShaderMaker> shaderMaker = nullptr;
        IBufferManager* bufferManager;
        MeshCreator* meshCreator;
        TransformUser* transformUser;
        IRendererMaker* renderCreator;
    public:
        IGCore(){};
        virtual ~IGCore(){};
        virtual WindowManager* getWinManager(){
            return nullptr;
        }
        virtual Time* manageTime(){
            return nullptr;
        }
        MeshCreator* allocate(){
            return meshCreator;
        }
        TransformUser* getTransform(){
            return transformUser;
        }
        IRendererMaker* render(){
            return renderCreator;
        }
        std::shared_ptr<IShaderMaker> getShaderMaker(){
            return std::move(shaderMaker);
        }
};

#endif