#pragma once
#ifndef EXAGON_PLUS_APP_HPP
#define EXAGON_PLUS_APP_HPP

//Reminder: Cambiar la implementacion de la carpeta pls en algun futuro
#include "../PEngine/PEngineMain.hpp"
#include <vector>

#include <iostream>

class ExagonPlus {
    public:
        ExagonPlus();
        ~ExagonPlus();
        void run();
};
//Test class (Finally)
class RenderTest : public Scene {
    private:
        IRenderer<WVertex3D>* simpleRenderer;
        Mesh<WVertex3D>* testMesh;
    public:
        RenderTest(PEngine* engine) : Scene(engine){}
        ~RenderTest(){}
        void init() override {
            context->getResourceManager().processShader()->loadShader("background", 
                {{ShaderPart::VERTEX, "EPGame/shaders/shape.vert"},{ShaderPart::FRAGMENT, "EPGame/shaders/shape.frag"}});
            simpleRenderer = context->getGraphics().render()->makeRenderer(context->getResourceManager().processShader()->getShader("background"));
            //Esto de aqui es un ejemplo de datos que yo puedo generar a traves de una clase o simplemente para cargar un modelo
            std::vector<WVertex3D> data = {
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
                {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 0.0f}}
            };
            std::vector<unsigned int> indexes = {
                0,1,3,
                1,2,3
            };
            testMesh = context->getGraphics().allocate()->createMesh(data, &indexes);
        }
        void show() override {
            simpleRenderer->draw(testMesh);
        }
};

#endif