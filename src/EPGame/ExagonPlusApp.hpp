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
        Renderer* simpleRenderer;
        Mesh<WVertex3D>* testMesh;
        Transform3D* t;
        //Variables de un objeto custom (ajeno a Object Engine)
        float ROTZ = 0.0f;
        float SPEEDZ = 30.0f;
    public:
        RenderTest(PEngine* engine) : Scene(engine){}
        ~RenderTest(){}
        void init() override {
            context->getResourceManager().processShader()->loadShader("background", 
                {{ShaderPart::VERTEX, "EPGame/shaders/shape.vert"},{ShaderPart::FRAGMENT, "EPGame/shaders/shape.frag"}});
            simpleRenderer = context->getGraphics().render()->makeRenderer(context->getResourceManager().processShader()->getShader("background"));
            Mat4f mat(1.0f);
            //context->getResourceManager().processShader()->getShader("background")->setFloat("Model", mat);
            
            //Hijo de
            for(int i=0 ; i<4; i++){
                for(int j=0; j<4; j++){
                    std::cout<<mat.mat4x4[i][j]<<" ";
                }
                std::cout<<"\n";
            }

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
            t = context->getGraphics().getTransform()->useTransform3D();
            //t->rotate(0.0f, 0.0f, 30.0f);
            //t->apply(context->getResourceManager().processShader()->getShader("background"), "Model");
        }
        void show() override {
            t->apply(context->getResourceManager().processShader()->getShader("background"), "Model");
            simpleRenderer->draw(testMesh);
        }
        void update(float dT) override {
            ROTZ+=dT*SPEEDZ;
            t->reset();
            t->rotate(0.0f, 0.0f, ROTZ);
        }
};

#endif