#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "GEngine/Engine.hpp"
#include "ExagonGameProcess.hpp"

#include <iostream>

class ExagonPanel {
    private:
        Engine engine;
        ExagonGameProcess game;
        GLFWwindow* window;
    public:
        //Constructor
        ExagonPanel(GLFWwindow* window);
        //Methods
        void paint();
        void clearEngine();
};

//Constructor
ExagonPanel::ExagonPanel(GLFWwindow* window):
    engine(),
    game(&engine)
{
    std::cout<<"Oh me creooo, dice Panel"<<std::endl;
    this->window = window;
    engine.fixScreenProportion(window);
}

void ExagonPanel::paint(){
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