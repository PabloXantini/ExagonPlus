#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "GEngine/Engine.hpp"
#include "ExagonGameProcess.hpp"

#include <iostream>

class ExagonPanel {
    private:
        Engine* engine;
        ExagonGameProcess game;
        //GLFWwindow* window;
    public:
        //Constructor
        ExagonPanel(Engine* engine);
        //Methods
        void run();
        void clearEngine();
};

//Constructor
ExagonPanel::ExagonPanel(Engine* engine):
    engine(engine),
    game(engine)
{
    std::cout<<"Oh me creooo, dice Panel"<<std::endl;
    //this->window = window;
    //engine->fixScreenProportion(window);
}

void ExagonPanel::run(){
    //El orden de renderizado
    //engine->fixScreenProportion(window);
    game.PlayLevel();
    game.getBG().show();
}

void ExagonPanel::clearEngine() {
    engine->clearBuffers();
    engine->clearShaders();
}

#endif