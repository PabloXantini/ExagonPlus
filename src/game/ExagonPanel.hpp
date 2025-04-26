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
        void show();
};

//Constructor
ExagonPanel::ExagonPanel(Engine* engine):
    engine(engine),
    game(engine)
{
    std::cout<<"Oh me creooo, dice Panel"<<std::endl;
}

void ExagonPanel::show(){
    //El orden de renderizado
    game.PlayLevel();
    //Background
    game.getBG().show();
    //Obstaculos
    game.getWall()->show();
    //Centro
    game.getCenter().show();
    //Jugador
    game.getPlayer().show();
}

#endif