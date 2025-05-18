#ifndef EXAGON_PANEL_HPP
#define EXAGON_PANEL_HPP

#include "GEngine/Engine.hpp"
#include "ExagonGameProcess.hpp"

#include <iostream>

class ExagonPanel {
    private:
        Engine* engine;
        AudioEngine* aengine;
        ExagonGameProcess game;
        //GLFWwindow* window;
    public:
        //Constructor
        ExagonPanel(Engine* engine, AudioEngine* aengine);
        //Methods
        void show();
};

//Constructor
ExagonPanel::ExagonPanel(Engine* engine, AudioEngine* aengine):
    engine(engine),
    aengine(aengine),
    game(engine, aengine)
{
    std::cout<<"Oh me creooo, dice Panel"<<std::endl;
}

void ExagonPanel::show(){
    //El orden de renderizado
    //game.PlayLevel();
    game.run();
    game.show();
}

#endif