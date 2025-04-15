#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "GEngine/Engine.hpp"
#include "ExagonGameProcess.hpp"

#include <vector>

class ExagonPanel {
    private:
        ExagonGameProcess game;
        Engine engine;
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
    game(engine)
{
    //setupBuffers();
}

void ExagonPanel::paint(GLFWwindow* window){
    //El orden de renderizado
    engine.fixScreenProportion(window);
    game.getBG().show();
}

void ExagonPanel::clearEngine() {
    engine.clearBuffers();
    engine.clearShaders();
}

#endif