#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP

#include "../../PEngine/PEngineMain.hpp"
#include "Game.hpp"
#include "States/Gameplay.hpp"

#include <memory>

enum class States {
    GAMEPLAY
};

class Game {
    private:
        std::unique_ptr<GameState> currentState;
    protected:
        PEngine* context;
    public:
        GameGlobalVariables global;
        Game(PEngine* engineContext) : context(engineContext){}
        ~Game(){
            //Sujeto a cambios
            std::cout<<"Ha caido el gaming"<<std::endl;
        }
        void init(){
            //Desktop: Window Setup
            global.mainWindow = context->getGraphics().getWinManager()->createWindow(800, 600, "ExagonPlus");
            //Loading Resources
            context->getResourceManager().processShader()->loadShader("background", 
                {{ShaderPart::VERTEX, "EPGame/shaders/shape.vert"},{ShaderPart::FRAGMENT, "EPGame/shaders/shape.frag"}});
            global.simpleRenderer = context->getGraphics().render()->makeRenderer(context->getResourceManager().processShader()->getShader("background"));
            //Set the initialstate
            startInState(std::make_unique<GamePlay>(context));
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
            switch(state){
                case States::GAMEPLAY:
                    changeState(std::make_unique<GamePlay>(context));
                    break;
            }
        }
        void run(){
            global.mainWindow->setScene(currentState.get());
            context->getGraphics().getWinManager()->runAsOnlyWindow(global.mainWindow);
        }        
};

#endif