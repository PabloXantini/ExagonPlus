#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "GEngine/Engine.hpp"
#include "ExagonGameProcess.hpp"

#include <iostream>

class ExagonPanel {
    private:
        Engine engine;
        ExagonGameProcess game;
    public:
        //Constructor
        ExagonPanel();
        //Methods
        void paint(GLFWwindow* window);
        void clearEngine();
};

//Constructor
ExagonPanel::ExagonPanel():
    engine(),
    game(&engine)
{
    std::cout<<"Oh me creooo, dice Panel"<<std::endl;
}

void ExagonPanel::paint(GLFWwindow* window){
    //El orden de renderizado
    engine.fixScreenProportion(window);
    game.PlayLevel();
    game.getBG().show();
}

void ExagonPanel::clearEngine() {
    engine.clearBuffers();
    engine.clearShaders();
}

#endif