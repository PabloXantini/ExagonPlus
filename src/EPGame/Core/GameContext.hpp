#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "../../PEngine/PEngineMain.hpp"
#include "Game.hpp"
#include "States/StateCreator.hpp"
//#include "States/Gameplay.hpp"

#include <memory>

/*
enum class States {
    GAMEPLAY
};
*/

class Game : public Scene {
    private:
        std::unordered_map<States, std::unique_ptr<StateCreator>> mapStates;
        std::unique_ptr<GameState> currentState;
    public:
        GameGlobalVariables global;
        Game(PEngine* engineContext) : Scene(engineContext){
            mapStates = initStateFacts();
        }
        ~Game(){
            //Sujeto a cambios
            std::cout<<"Ha caido el gaming"<<std::endl;
        }
        void init() override {
            //Desktop: Window Setup
            global.mainWindow = context->getGraphics().getWinManager()->createWindow(800, 600, "ExagonPlus");
            //Loading Resources
            context->getResourceManager().processShader()->loadShader("background", 
                {{ShaderPart::VERTEX, "EPGame/shaders/shape.vert"},{ShaderPart::FRAGMENT, "EPGame/shaders/shape.frag"}});
            global.simpleRenderer = context->getGraphics().render()->makeRenderer(context->getResourceManager().processShader()->getShader("background"));
            //Set the initialstate
            startInState(mapStates[States::GAMEPLAY]->createState(context));
            //Example: Setup a shared contexts
            //global.otherWindow = context->getGraphics().getWinManager()->createWindow(800, 600, "ExagonPlus Second Window", false, 1U, global.mainWindow);
        }
        void startInState(std::unique_ptr<GameState> initialState){
            this->currentState = std::move(initialState);
            this->currentState->setGameContext(this);
            this->currentState->init();
        }
        void changeState(std::unique_ptr<GameState> nextState){
            this->currentState->close();
            this->currentState = std::move(nextState);
            this->currentState->setGameContext(this);
            this->currentState->init();
        }
        //Implementacion de estados
        void callState(States state){
            mapStates[state]->createState(context);
        }
        void run(){
            global.mainWindow->setScene(this);
            //global.otherWindow->setScene(this);
            context->getGraphics().getWinManager()->runAsOnlyWindow(global.mainWindow);
            //context->getGraphics().getWinManager()->runAsVariousWindows(global.mainWindow);
        }
        void update(float dT) override {
            currentState->update(dT);
        }
        void show() override {
            currentState->show();
        }
};

#endif