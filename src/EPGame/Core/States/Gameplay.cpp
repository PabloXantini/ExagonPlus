#include "Gameplay.hpp"
#include "../../../PEngine/PEngineMain.hpp"
#include "../GameContext.hpp"

GamePlay::GamePlay(PEngine* engine) : GameState(engine){
    std::cout<<"Empieza el gameplay"<<std::endl;
}
GamePlay::~GamePlay(){
    std::cout<<"Bye gameplay"<<std::endl;
}
void GamePlay::init(){
    //context->getResourceManager().processShader()->loadShader("background", 
    //    {{ShaderPart::VERTEX, "EPGame/shaders/shape.vert"},{ShaderPart::FRAGMENT, "EPGame/shaders/shape.frag"}});
    //simpleRenderer = context->getGraphics().render()->makeRenderer(context->getResourceManager().processShader()->getShader("background"));
    
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
    auto testMesh = context->getGraphics().allocate()->createMesh(data, &indexes);
    model = context->getGraphics().model()->createModel();
    model->addMesh(std::move(testMesh));
    rectangle = context->createGameObject3D(this->gameReference->global.simpleRenderer);
    rectangle->attachModel(model);
}
void GamePlay::update(float dT){
    ROTZ+=dT*SPEEDZ;
    TX+=dT*SPEEDTX;
    if(TX>0.5f){
        SPEEDTX=-SPEEDTX;
    }else if (TX<-0.5f){
        SPEEDTX=-SPEEDTX;
    }
    std::cout<<rectangle->getTransform()->getPosition().X<<"\n";
    //std::cout<<rectangle->getTransform()->getPosition().Y<<"\n";
    //std::cout<<rectangle->getTransform()->getPosition().Z<<"\n";
    rectangle->getTransform()->reset();
    //rectangle->getTransform()->rotate(0.0f, 0.0f, ROTZ);
    rectangle->getTransform()->translate({TX, 0.0f, 0.0f});
}
void GamePlay::show(){
    context->getResourceManager().processShader()->getShader("background")->use();
    rectangle->getTransform()->apply(context->getResourceManager().processShader()->getShader("background"), "Model");
    rectangle->draw();
}