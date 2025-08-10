#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../../PEngine/Utils/Scene.hpp"

#include <iostream>

class Game;

class GameState : public Scene {
    protected:
        Game* gameReference;
    public:
        GameState(PEngine* context) : Scene(context){}
        virtual ~GameState(){}
        void setGameContext(Game* gameContext){
            this->gameReference = gameContext;
        }
};

#endif